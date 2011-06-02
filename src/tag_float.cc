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
    TagFloat::TagFloat(const std::string &name, const float &value)
        : Tag(name), _value(value)
    {
    }


    TagFloat::TagFloat(const TagFloat &t)
        : Tag(t.getName()), _value(t.getValue())
    {
    }

    
    float TagFloat::getValue() const
    {
        return _value;
    }


    void TagFloat::setValue(const float &value)
    {
        _value = value;
    }


    uint8_t TagFloat::getType() const
    {
        return TAG_FLOAT;
    }


    ByteArray TagFloat::toByteArray() const
    {
        ByteArray ret = Tag::toByteArray();

        const uint8_t *split = reinterpret_cast<const uint8_t *>(&_value);

        for (int i = 3; i >= 0; --i)
            ret.push_back(split[i]);

        return ret;
    }


    std::string TagFloat::toString() const
    {
        std::stringstream ret;
        
        ret << "TAG_Float";
        
        if (!_name.empty())
            ret << "(\"" << _name << "\")";
        
        ret << ": " << _value;

        return ret.str();
    }

    Tag *TagFloat::clone() const
    {
        return new TagFloat(_name, _value);
    }
}
