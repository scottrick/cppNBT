/*
 * Copyright (C) 2012 Scott Atkins
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
    TagIntArray::TagIntArray(const std::string &name, const IntArray &value) 
        : Tag(name)
    {
        _value = value;
    }


    TagIntArray::TagIntArray(const TagIntArray &t) : Tag(t.getName())
    {
        _value = t.getValue();
    }

    
    IntArray TagIntArray::getValue() const
    {
        return _value;
    }


    void TagIntArray::setValue(const IntArray &value)
    {
        _value = value;
    }


    uint8_t TagIntArray::getType() const
    {
        return TAG_BYTE_ARRAY;
    }


    ByteArray TagIntArray::toByteArray() const
    {
        ByteArray ret = Tag::toByteArray();

        int32_t len = _value.size();
        uint8_t *split = reinterpret_cast<uint8_t *>(&len);

        for (int i = 3; i >= 0; --i)
            ret.push_back(split[i]);

        for (int k = 0; k < len; ++k) 
        {
            split = reinterpret_cast<uint8_t *>(_value[k]);

            for (int i = 3; i >= 0; --i)
                ret.push_back(split[i]);
        }

        return ret;
    }


    std::string TagIntArray::toString() const
    {
        std::stringstream ret;
        
        ret << "TAG_Int_Array";
        
        if (!_name.empty())
            ret << "(\"" << _name << "\")";
        
        ret << ": ";

		ret << _value.size() << " ints";

		//comment this out if you wanna see the raw data
        //for (size_t i = 0; i < _value.size(); ++i)
        //{
        //    ret << "0x";
        //    ret.width(2);
        //    ret.fill('0');
        //    ret << std::hex << (int)_value[i] << " ";
        //}

        return ret.str();
    }

    Tag* TagIntArray::clone() const
    {
        return new TagIntArray(_name, _value);
    }
}
