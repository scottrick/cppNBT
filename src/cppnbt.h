/*
* Copyright (C) 2011 Lukas Niederbremer
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
#ifndef CPPNBT_H
#define CPPNBT_H

#include <string>
#include <sstream>
#include <list>
#include <vector>
#include <stdexcept>
#include <functional>
#include <cerrno>
#include <zlib.h>

#include <stdint.h>

namespace nbt
{
    std::string string_replace(const std::string &string, 
                           const std::string &find,
                           const std::string &replace);


    template <typename T>
    void flipBytes(T &val)
    {
        size_t size = sizeof(val);
        T retval;

        uint8_t *src = reinterpret_cast<uint8_t *>(&val);
        uint8_t *dst = reinterpret_cast<uint8_t *>(&retval);

        for (size_t i = 0; i < size; ++i)
            dst[i] = src[size - (i + 1)];

        val = retval;
    }

    bool is_big_endian();

    
    class GzipIOException : public std::runtime_error
    {
        public:
            GzipIOException(int code)
                : std::runtime_error("Gzip IO error"), code(code) {}

            int getCode() { return code; }

        private:
            int code;
    };

    class KeyNotFoundException : public std::runtime_error
    {
        public:
            KeyNotFoundException() 
                : std::runtime_error("key not found in compound") {}
    };

    class EmptyListException : public std::runtime_error
    {
        public:
            EmptyListException()
                : std::runtime_error("list is empty") {}
    };

    typedef std::vector<unsigned char> ByteArray;

    enum
    {
        TAG_END        = 0,
        TAG_BYTE       = 1,
        TAG_SHORT      = 2,
        TAG_INT        = 3,
        TAG_LONG       = 4,
        TAG_FLOAT      = 5,
        TAG_DOUBLE     = 6,
        TAG_BYTE_ARRAY = 7,
        TAG_STRING     = 8,
        TAG_LIST       = 9,
        TAG_COMPOUND   = 10
    };


    class Tag
    {
        public:
            // Constructors
            Tag(const std::string &name);
            Tag(const Tag &t);

            virtual ~Tag();

            // Get and set name
            std::string getName() const;
            void setName(const std::string &name);

            // Get type name and ID
            std::string getTypeName() const;
            static std::string getTypeName(uint8_t type);

            virtual uint8_t getType() const;
            virtual ByteArray toByteArray() const;
            virtual std::string toString() const;

            virtual Tag* clone() const = 0;

        protected:
            std::string _name;
    };


    class TagByteArray : public Tag
    {
        public:
            TagByteArray(const std::string &name,
                         const ByteArray &value = ByteArray());
            TagByteArray(const TagByteArray &t);

            ByteArray getValue() const;
            void setValue(const ByteArray &value);

            virtual uint8_t getType() const;
            virtual ByteArray toByteArray() const;
            virtual std::string toString() const;

            virtual Tag *clone() const;

        protected:
            ByteArray _value;
    };


    class TagByte : public Tag
    {
        public:
            TagByte(const std::string &name, const int8_t &value = 0);
            TagByte(const TagByte &t);

            int8_t getValue() const;
            void setValue(const int8_t &value);

            virtual uint8_t getType() const;
            virtual ByteArray toByteArray() const;
            virtual std::string toString() const;

            virtual Tag *clone() const;

        protected:
            int8_t _value;
    };


    class TagCompound : public Tag
    {
        public:
            TagCompound(const std::string &name = "",
                        const std::list<Tag *> &value  = 
                            std::list<Tag *>());
            TagCompound(const TagCompound &t);

            ~TagCompound();

            std::list<Tag *> getValue() const;
            void setValue(std::list<Tag *> value);

            void insert(const Tag &tag);
            void insert(Tag *tag);
            void remove(const std::string &name);

            std::vector<std::string> getKeys() const;
            std::vector<Tag *> getValues() const;
            Tag *getValueAt(const std::string &key) const;

            virtual uint8_t getType() const;
            virtual ByteArray toByteArray() const;
            virtual std::string toString() const;

            virtual Tag *clone() const;

        protected:
            std::list<Tag *> _value;
    };


    class TagDouble : public Tag
    {
        public:
            TagDouble(const std::string &name, const double &value = 0);
            TagDouble(const TagDouble &t);

            double getValue() const;
            void setValue(const double &value);

            virtual uint8_t getType() const;
            virtual ByteArray toByteArray() const;
            virtual std::string toString() const;

            virtual Tag *clone() const;

        protected:
            double _value;
    };


    class TagEnd : public Tag
    {
        public:
            TagEnd();
            TagEnd(const TagEnd &t);

            virtual uint8_t getType() const;
            virtual std::string toString() const;

            virtual Tag *clone() const;

    };


    class TagFloat : public Tag
    {
        public:
            TagFloat(const std::string &name, const float &value = 0);
            TagFloat(const TagFloat &t);

            float getValue() const;
            void setValue(const float &value);

            virtual uint8_t getType() const;
            virtual ByteArray toByteArray() const;
            virtual std::string toString() const;

            virtual Tag *clone() const;

        protected:
            float _value;
    };


    class TagInt : public Tag
    {
        public:
            TagInt(const std::string &name, const int32_t &value = 0);
            TagInt(const TagInt &t);

            int32_t getValue() const;
            void setValue(const int32_t &value);

            virtual uint8_t getType() const;
            virtual ByteArray toByteArray() const;
            virtual std::string toString() const;

            virtual Tag *clone() const;

        protected:
            int32_t _value;
    };


    class TagList : public Tag
    {
        public:
            TagList(const uint8_t &type,
                    const std::string &name, 
                    const std::vector<Tag *> &value = std::vector<Tag *>());
            TagList(const TagList &t);

            ~TagList();

            std::vector<Tag *> getValue() const;
            void setValue(const std::vector<Tag *> &value);

            uint8_t getChildType() const;
            void setChildType(const uint8_t &value);

            void append(const Tag &value);
            void append(Tag *value);

            void removeFirst();
            void removeLast();
            void remove(Tag *tag);
            void remove(size_t i);
            void clear();

            Tag *at(size_t i) const;
            Tag *back() const;
            Tag *front() const;

            Tag *operator[](size_t index) const;
            TagList &operator<<(const Tag &tag);

            size_t size() const;                

            virtual uint8_t getType() const;
            virtual ByteArray toByteArray() const;
            virtual std::string toString() const;

            virtual Tag *clone() const;

        protected:
            uint8_t _childType;
            std::vector<Tag *> _value;

    };


    class TagLong : public Tag
    {
        public:
            TagLong(const std::string &name, const int64_t &value = 0);
            TagLong(const TagLong &t);

            int64_t getValue() const;
            void setValue(const int64_t &value);

            virtual uint8_t getType() const;
            virtual ByteArray toByteArray() const;
            virtual std::string toString() const;

            virtual Tag *clone() const;

        protected:
            int64_t _value;
    };


    class TagShort : public Tag
    {
        public:
            TagShort(const std::string &name, const int16_t &value = 0);
            TagShort(const TagShort &t);

            int16_t getValue() const;
            void setValue(const int16_t &value);

            virtual uint8_t getType() const;
            virtual ByteArray toByteArray() const;
            virtual std::string toString() const;

            virtual Tag *clone() const;

        protected:
            int16_t _value;
    };


    class TagString : public Tag
    {
        public:
            TagString(const std::string &name, const std::string &value = "");
            TagString(const TagString &t);

            std::string getValue() const;
            void setValue(const std::string &value);

            virtual uint8_t getType() const;
            virtual ByteArray toByteArray() const;
            virtual std::string toString() const;

            virtual Tag *clone() const;

        protected:
            std::string _value;
    };

    class NbtFile
    {
        typedef Tag *(NbtFile::*NbtMembFn)();

        public:
            NbtFile();
            NbtFile(const std::string &fname);
            virtual ~NbtFile();

            void open(const std::string &fname = "",
                      const std::string &flags = "r");
            void close();
            void read();
            void write();

            Tag *getRoot() const;
            void setRoot(const Tag &r);

        protected:
            NbtMembFn getReader(uint8_t type);

            Tag *readTag();

            Tag *readByte();
            Tag *readShort();
            Tag *readInt();
            Tag *readLong();
            Tag *readFloat();
            Tag *readDouble();
            Tag *readByteArray();
            Tag *readString();
            Tag *readList();
            Tag *readCompound();

            std::string _fname;
            Tag *_root;

            gzFile _file;
    };
}


#endif
