/*******************************************************************************
 *
 *  NBT File for reading and writing (nbtfile.cc)
 *  ---
 *  Created: 28.05.2011 04:06:12
 *  Author:  Lukas Niederbremer
 *
 ******************************************************************************/
#include "nbtfile.h"

namespace nbt
{
    typedef Tag *(NbtFile::*NbtMembFn)(); // Again...

    NbtFile::NbtFile()
        : _fname(""), _root(NULL), _file(Z_NULL)
    {
        // empty
    }

    NbtFile::NbtFile(const std::string &fname)
        : _fname(fname), _root(NULL)
    {
        open(fname);
    }

    NbtFile::~NbtFile()
    {
        delete _root;
        close();
    }

    void NbtFile::read()
    {
        if (_file == Z_NULL)
            throw GzipIOException(0);

        _root = readTag(); // Read root

        return;
    }

    void NbtFile::write()
    {
        if (_file == Z_NULL)
            throw GzipIOException(0);

        ByteArray bs = _root->toByteArray();

        ByteArray::const_iterator i;
        for (i = bs.begin(); i != bs.end(); ++i)
            gzputc(_file, *i);

        return;
    }

    Tag *NbtFile::getRoot() const
    {
        return _root;
    }

    void NbtFile::setRoot(const Tag &r)
    {
        delete _root;
        _root = r.clone();
    }

    void NbtFile::open(const std::string &fname, const std::string &flags)
    {
        if (_file != Z_NULL)
            close();

        const char *name = ((fname == "") ? _fname : fname).c_str();
        _file = gzopen(name, flags.c_str());
        if (_file == Z_NULL)
            throw GzipIOException(errno);
    }

    void NbtFile::close()
    {
        gzclose(_file);
    }

    NbtMembFn NbtFile::getReader(uint8_t type)
    {
        switch (type)
        {
            case TAG_BYTE:       return &NbtFile::readByte;
            case TAG_SHORT:      return &NbtFile::readShort;
            case TAG_INT:        return &NbtFile::readInt;
            case TAG_LONG:       return &NbtFile::readLong;
            case TAG_FLOAT:      return &NbtFile::readFloat;
            case TAG_DOUBLE:     return &NbtFile::readDouble;
            case TAG_BYTE_ARRAY: return &NbtFile::readByteArray;
            case TAG_STRING:     return &NbtFile::readString;
            case TAG_LIST:       return &NbtFile::readList;
            case TAG_COMPOUND:   return &NbtFile::readCompound;
            default: return NULL; // Also bogus
        }
    }

    Tag *NbtFile::readTag()
    {
        uint8_t type = 0;

        gzread(_file, &type, 1);
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


    Tag *NbtFile::readByte()
    {
        uint8_t byte;
        gzread(_file, &byte, 1);

        return new TagByte("", byte);
    }

    Tag *NbtFile::readShort()
    {
        int16_t val;
        gzread(_file, &val, 2);

        if (!is_big_endian())
            flipBytes<int16_t>(val);

        return new TagShort("", val);
    }

    Tag *NbtFile::readInt()
    {
        int32_t val;
        gzread(_file, &val, 4);

        if (!is_big_endian())
            flipBytes<int32_t>(val);

        return new TagInt("", val);
    }

    Tag *NbtFile::readLong()
    {
        int64_t val;
        gzread(_file, &val, 8);

        if (!is_big_endian())
            flipBytes<int64_t>(val);

        return new TagLong("", val);
    }

    Tag *NbtFile::readFloat()
    {
        float val;
        gzread(_file, &val, 4);

        if (!is_big_endian())
            flipBytes<float>(val);

        return new TagFloat("", val);
    }

    Tag *NbtFile::readDouble()
    {
        double val;
        gzread(_file, &val, 8);

        if (!is_big_endian())
            flipBytes<double>(val);

        return new TagDouble("", val);
    }

    Tag *NbtFile::readByteArray()
    {
        int32_t len;
        gzread(_file, &len, 4);

        if (!is_big_endian())
            flipBytes<int32_t>(len);

        ByteArray ba(len);
        for (int i = 0; i < len; ++i)
        {
            uint8_t byte;
            gzread(_file, &byte, 1);

            ba.push_back(byte);
        }

        return new TagByteArray("", ba);
    }

    Tag *NbtFile::readString()
    {
        int16_t len;
        gzread(_file, &len, 2);

        if (!is_big_endian())
            flipBytes<int16_t>(len);

        std::string str;
        for (int i = 0; i < len; ++i)
        {
            // TODO: Read blocks
            uint8_t ch;
            gzread(_file, &ch, 1);
            str.push_back(ch);
        }

        return new TagString("", str);
    }

    Tag *NbtFile::readList()
    {
        int8_t childType;
        int32_t len;

        gzread(_file, &childType, 1);
        gzread(_file, &len, 4);

        TagList *ret = new TagList(childType, "");

        if (!is_big_endian())
            flipBytes<int32_t>(len);

        NbtMembFn reader = getReader(childType);
        for (int i = 0; i < len; ++i)
        {
            Tag *child = (this->*reader)();
            ret->append(*child);
            delete child;
        }

        return ret;
    }

    Tag *NbtFile::readCompound()
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

            ret->insert(*child);
            delete child;
        }

        return ret;
    }
}
