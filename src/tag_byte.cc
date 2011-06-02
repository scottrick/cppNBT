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
    TagByte::TagByte(const std::string &name, const int8_t &value)
        : Tag(name), _value(value)
    {
    }


    TagByte::TagByte(const TagByte &t)
        : Tag(t.getName()), _value(t.getValue())
    {
    }

    
    int8_t TagByte::getValue() const
    {
        return _value;
    }


    void TagByte::setValue(const int8_t &value)
    {
        _value = value;
    }


    uint8_t TagByte::getType() const
    {
        return TAG_BYTE;
    }


    ByteArray TagByte::toByteArray() const
    {
        ByteArray ret = Tag::toByteArray();

        ret.push_back(_value);

        return ret;
    }


    std::string TagByte::toString() const
    {
        std::stringstream ret;

        ret << "TAG_Byte";

        if (!_name.empty())
            ret << "(\"" << _name << "\")";
        
        ret << ": " << static_cast<int>(_value);

        return ret.str();
    }

    Tag* TagByte::clone() const
    {
        return new TagByte(_name, _value);
    }
}
