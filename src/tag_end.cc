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
    TagEnd::TagEnd() : Tag("")
    {
        // Do nothing
    }


    TagEnd::TagEnd(const TagEnd &t) : Tag(t.getName())
    {
        // Do nothing
    }

    
    uint8_t TagEnd::getType() const
    {
        return TAG_END;
    }


    std::string TagEnd::toString() const
    {
        return "TAG_End";
    }

    Tag *TagEnd::clone() const
    {
        return new TagEnd();
    }
}
