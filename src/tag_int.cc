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
    TagInt::TagInt(const std::string &name, const int32_t &value)
        : Tag(name), _value(value)
    {
    }

    
    TagInt::TagInt(const TagInt &t)
        : Tag(t.getName()), _value(t.getValue())
    {
    }


    int32_t TagInt::getValue() const
    {
        return _value;
    }


    void TagInt::setValue(const int32_t &value)
    {
        _value = value;
    }


    uint8_t TagInt::getType() const
    {
        return TAG_INT;
    }


    ByteArray TagInt::toByteArray() const
    {
        ByteArray ret = Tag::toByteArray();

        const uint8_t *split = reinterpret_cast<const uint8_t *>(&_value);

        for (int i = 3; i >= 0; --i)
            ret.push_back(split[i]);

        return ret;
    }


    std::string TagInt::toString() const
    {
        std::stringstream ret;

        ret << "TAG_Int";

        if (!_name.empty())
            ret << "(\"" << _name << "\")";
        
        ret << ": " << _value;

        return ret.str();
    }

    Tag *TagInt::clone() const
    {
        return new TagInt(_name, _value);
    }
}
