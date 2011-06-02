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
#include "cppnbt.h"

namespace nbt
{
    std::string string_replace(const std::string &string,
            const std::string &find,
            const std::string &replace)
    {
        std::string ret = string;

        for (int j = 0; (j = ret.find(find, j)) != std::string::npos;)
            ret.replace(j++, find.length(), replace);

        return ret;
    }

    bool is_big_endian()
    {
        union
        {
            uint32_t i;
            char c[4];
        } bint = {0x01020304};

        return bint.c[0] == 1;
    }
}
