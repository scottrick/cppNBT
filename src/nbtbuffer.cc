/*
 * Copyright (C) 2012 Scott Atkins
 *
 * This file is part of cppNBT
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */
#include "cppnbt.h"

#include <cassert>
#include <iostream>

namespace nbt
{
    typedef Tag *(NbtBuffer::*NbtMembFn)(); // Again...

    NbtBuffer::NbtBuffer()
        : _root(NULL), _buffer(NULL)
    {

    }

    NbtBuffer::NbtBuffer(uint8_t *compressedBuffer, unsigned int length)
        : _root(NULL), _buffer(NULL)
    {
        read(compressedBuffer, length);
    }

    NbtBuffer::~NbtBuffer()
    {
        delete _root;
    }

    void NbtBuffer::read(uint8_t *compressedBuffer, unsigned int length)
    {
        uLongf BUFF_SIZE = length * 128;
        uint8_t *inflatedBuffer = new uint8_t[BUFF_SIZE];
        memset(inflatedBuffer, 0, BUFF_SIZE);

        int result = uncompress(inflatedBuffer, &BUFF_SIZE, compressedBuffer, length);
        assert(result == Z_OK);

        //setup the buffer stream
        _buffer = inflatedBuffer;

        if (_root)
        {
            delete _root;
            _root = NULL;
        }

        //read root
        _root = readTag();

        //all done reading, clean-up
        _buffer = NULL;
        delete[] inflatedBuffer;
    }

    NbtMembFn NbtBuffer::getReader(uint8_t type)
    {
        switch (type)
        {
            case TAG_BYTE:       return &NbtBuffer::readByte;
            case TAG_SHORT:      return &NbtBuffer::readShort;
            case TAG_INT:        return &NbtBuffer::readInt;
            case TAG_LONG:       return &NbtBuffer::readLong;
            case TAG_FLOAT:      return &NbtBuffer::readFloat;
            case TAG_DOUBLE:     return &NbtBuffer::readDouble;
            case TAG_BYTE_ARRAY: return &NbtBuffer::readByteArray;
            case TAG_STRING:     return &NbtBuffer::readString;
            case TAG_LIST:       return &NbtBuffer::readList;
            case TAG_COMPOUND:   return &NbtBuffer::readCompound;
            case TAG_INT_ARRAY:  return &NbtBuffer::readIntArray;
            default: return NULL; // Also bogus
        }
    }

    Tag *NbtBuffer::readTag()
    {
        uint8_t type = *((uint8_t *)_buffer);
        _buffer += sizeof(uint8_t);

        if (type == TAG_END)
            return new TagEnd();

        Tag *nameTag = readString();
        TagString *nameTagStr = dynamic_cast<TagString *>(nameTag);

        NbtMembFn reader = getReader(type);
        Tag *res = (this->*reader)();
        res->setName(nameTagStr->getValue());

        delete nameTag;
        return res;
    }

    Tag *NbtBuffer::readByte()
    {
        uint8_t byte = *((uint8_t *)_buffer);
        _buffer += sizeof(uint8_t);

        return new TagByte("", byte);
    }

    Tag *NbtBuffer::readShort()
    {
        int16_t val = *((int16_t *)_buffer);
        _buffer += sizeof(int16_t);

        if (!is_big_endian())
            flipBytes<int16_t>(val);

        return new TagShort("", val);
    }

    Tag *NbtBuffer::readInt()
    {
        int32_t val = *((int32_t *)_buffer);
        _buffer += sizeof(int32_t);

        if (!is_big_endian())
            flipBytes<int32_t>(val);

        return new TagInt("", val);
    }

    Tag *NbtBuffer::readIntArray()
    {
        int32_t len = *((int32_t *)_buffer);
        _buffer += sizeof(int32_t);

        if (!is_big_endian())
            flipBytes<int32_t>(len);

        IntArray ia;
        for (int i = 0; i < len; ++i)
        {
            int32_t val = *((int32_t *)_buffer);
            _buffer += sizeof(int32_t);

            if (!is_big_endian())
                flipBytes<int32_t>(val);

            ia.push_back(val);
        }

        return new TagIntArray("", ia);
    }


    Tag *NbtBuffer::readLong()
    {
        int64_t val = *((int64_t *)_buffer);
        _buffer += sizeof(int64_t);

        if (!is_big_endian())
            flipBytes<int64_t>(val);

        return new TagLong("", val);
    }

    Tag *NbtBuffer::readFloat()
    {
        float val = *((float *)_buffer);
        _buffer += sizeof(float);

        if (!is_big_endian())
            flipBytes<float>(val);

        return new TagFloat("", val);
    }

    Tag *NbtBuffer::readDouble()
    {
        double val = *((double *)_buffer);
        _buffer += sizeof(double);

        if (!is_big_endian())
            flipBytes<double>(val);

        return new TagDouble("", val);
    }

    Tag *NbtBuffer::readByteArray()
    {
        int32_t len = *((int32_t *)_buffer);
        _buffer += sizeof(int32_t);

        if (!is_big_endian())
            flipBytes<int32_t>(len);

        ByteArray ba;
        for (int i = 0; i < len; ++i)
        {
            uint8_t byte = *((uint8_t *)_buffer);
            _buffer += sizeof(uint8_t);

            ba.push_back(byte);
        }

        return new TagByteArray("", ba);
    }

    Tag *NbtBuffer::readString()
    {
        int16_t len = *((int16_t *)_buffer);
        _buffer += sizeof(int16_t);

        if (!is_big_endian())
            flipBytes<int16_t>(len);

        std::string str;
        for (int i = 0; i < len; ++i)
        {
            // TODO: Read blocks
            uint8_t ch = *_buffer;
            _buffer += sizeof(uint8_t);
            str.push_back(ch);
        }
        
        return new TagString("", str);
    }

    Tag *NbtBuffer::readList()
    {
        int8_t childType = *((int8_t *)_buffer);
        _buffer += sizeof(int8_t);

        int32_t len = *((int32_t *)_buffer);
        _buffer += sizeof(int32_t);

        TagList *ret = new TagList(childType, "");

        if (!is_big_endian())
            flipBytes<int32_t>(len);

        NbtMembFn reader = getReader(childType);
        for (int i = 0; i < len; ++i)
        {
            Tag *child = (this->*reader)();
            ret->append(child);
        }

        return ret;
    }

    Tag *NbtBuffer::readCompound()
    {
        Tag *child = NULL;
        TagCompound *ret = new TagCompound("");

        while (((child = readTag()) != NULL))
        {
            if (child->getType() == TAG_END)
            {
                delete child;
                break;
            }

            ret->insert(child);
        }

        return ret;
    }
    
    Tag *NbtBuffer::getRoot() const
    {
        return _root;
    }

    void NbtBuffer::setRoot(const Tag &r)
    {
        delete _root;
        _root = r.clone();
    }
}