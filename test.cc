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
#include <iostream>

#include "src/cppnbt.h"

using namespace std;
using namespace nbt;

void dumpTag(Tag *t)
{
    nbt::ByteArray b = t->toByteArray();

    for (size_t i = 0; i < b.size(); ++i)
    {
        cout << "0x";
        cout.width(2);
        cout.fill('0');
        cout << hex << (int)b[i] << " ";
    }

    cout << endl;
}

int main(int argc, char **argv)
{
    NbtFile f;

    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " <nbtfile>" << std::endl;
        return 1;
    }

    try
    {
        f.open(argv[1]);
        f.read();

        Tag *root = f.getRoot();
        std::cout << root->toString() << std::endl;

    }
    catch (GzipIOException &gzioe)
    {
        std::cerr << "Unable to load NBT file " << argv[1] << ": "
                  << gzioe.getCode() << std::endl;
    }

    return 0;
}
