/*
 * Copyright (C) 2011 Scott Atkins
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
        : _root(NULL)
    {

    }

    NbtBuffer::NbtBuffer(unsigned char *buffer, unsigned int length)
        : _root(NULL)
    {
        read(buffer, length);
    }

    NbtBuffer::~NbtBuffer()
    {
        delete _root;
    }

    void NbtBuffer::read(unsigned char *buffer, unsigned int length)
    {
        uLongf BUFF_SIZE = length * 128;
        unsigned char *tempBuffer = new unsigned char[BUFF_SIZE];
        memset(tempBuffer, 0, BUFF_SIZE);

        int result = uncompress(tempBuffer, &BUFF_SIZE, buffer, length);

        if (result != Z_OK)
        {
            assert(result == Z_OK);
            std::cout << "result: " << result << std::endl;
        }

        delete[] tempBuffer;
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