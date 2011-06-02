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
    TagShort::TagShort(const std::string &name, const int16_t &value)
        : Tag(name), _value(value)
    {
    }


    TagShort::TagShort(const TagShort &t)
        : Tag(t.getName()), _value(t.getValue())
    {
    }

    
    int16_t TagShort::getValue() const
    {
        return _value;
    }


    void TagShort::setValue(const int16_t &value)
    {
        _value = value;
    }


    uint8_t TagShort::getType() const
    {
        return TAG_SHORT;
    }


    ByteArray TagShort::toByteArray() const
    {
        ByteArray ret = Tag::toByteArray();

        const uint8_t *split = reinterpret_cast<const uint8_t *>(&_value);

        for (int i = 1; i >= 0; --i)
            ret.push_back(split[i]);

        return ret;
    }


    std::string TagShort::toString() const
    {
        std::stringstream ret;
        
        ret << "TAG_Short";
        
        if (!_name.empty())
            ret << "(\"" << _name << "\")";
        
        ret << ": " << _value;

        return ret.str();
    }

    Tag *TagShort::clone() const
    {
        return new TagShort(_name, _value);
    }
}
