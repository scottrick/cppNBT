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

#include "tags.h"

namespace nbt
{
    class NbtFile
    {
        public:
            NbtFile();
            virtual ~NbtFile();

            void read(const std::string &fname);
            void write(const std::string &fname);

            Tag *getRoot() const;
            void setRoot(const Tag &r);

        protected:
            Tag *_root;

            gzFile open(const std::string &fname, const std::string &mode = "w");
            void close(gzFile &f);
    };
}

#endif
