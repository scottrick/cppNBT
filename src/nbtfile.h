/*******************************************************************************
 *
 *  NBT File for reading and writing (nbtfile.h)
 *  ---
 *  Created: 28.05.2011 03:49:33
 *  Author:  Lukas Niederbremer
 *
 ******************************************************************************/
#ifndef NBTFILE_H
#define NBTFILE_H

// gzip compression
#include <zlib.h>
#include <string>
#include <stdexcept>
#include <cerrno>

#include "cppnbt.h"

namespace nbt
{
    class GzipIOException : public std::runtime_error
    {
        public:
            GzipIOException(int code)
                : std::runtime_error("Gzip IO error"), code(code) {}

            int getCode() { return code; }

        private:
            int code;
    };

    class NbtFile
    {
        typedef Tag *(NbtFile::*NbtMembFn)();

        public:
            NbtFile();
            NbtFile(const std::string &fname);
            virtual ~NbtFile();

            void open(const std::string &fname = "", const std::string &flags = "r");
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
