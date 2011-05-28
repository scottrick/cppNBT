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
    NbtFile::NbtFile()
        : _root(NULL)
    {
        // empty
    }

    NbtFile::~NbtFile()
    {
        delete _root;
    }

    void NbtFile::read(const std::string &fname)
    {
        gzFile f = open(fname);

        // TODO: Magic

        return close(f);
    }

    void NbtFile::write(const std::string &fname)
    {
        gzFile f = open(fname);
        ByteArray bs = _root->toByteArray();

        ByteArray::const_iterator i;
        for (i = bs.begin(); i != bs.end(); ++i)
            gzputc(f, *i);

        return close(f);
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

    gzFile NbtFile::open(const std::string &fname, const std::string &mode)
    {
        // TODO: Error handling and exception throwing for bad files
        return gzopen(fname.c_str(), mode.c_str());
    }

    void NbtFile::close(gzFile &f)
    {
        gzclose(f);
    }
}
