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
    TagLong::TagLong(const std::string &name, const int64_t &value)
        : Tag(name), _value(value)
    {
    }


    TagLong::TagLong(const TagLong &t)
        : Tag(t.getName()), _value(t.getValue())
    {
    }

    
    int64_t TagLong::getValue() const
    {
        return _value;
    }


    void TagLong::setValue(const int64_t &value)
    {
        _value = value;
    }


    uint8_t TagLong::getType() const
    {
        return TAG_LONG;
    }


    ByteArray TagLong::toByteArray() const
    {
        ByteArray ret = Tag::toByteArray();

        const uint8_t *split = reinterpret_cast<const uint8_t *>(&_value);

        for (int i = 7; i >= 0; --i)
            ret.push_back(split[i]);

        return ret;
    }


    std::string TagLong::toString() const
    {
        std::stringstream ret;
        
        ret << "TAG_Long";
        
        if (!_name.empty())
            ret << "(\"" << _name << "\")";
        
        ret << ": " << _value;

        return ret.str();
    }

    Tag *TagLong::clone() const
    {
        return new TagLong(_name, _value);
    }
}
