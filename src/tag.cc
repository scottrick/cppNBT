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
    Tag::Tag(const std::string &name)
    {
        // Create a new Tag
        _name = name;
    }


    Tag::Tag(const Tag &t)
    {
        // Copy from another one
        _name = t.getName();
    }


    Tag::~Tag() {}


    std::string Tag::getName() const
    {
        return _name;
    }


    void Tag::setName(const std::string &name)
    {
        // Assign a new name
        _name = name;
    }


    uint8_t Tag::getType() const
    {
        // The super class Tag has no type yet, this is overriden by
        // derived classes

        return -1;
    }


    std::string Tag::getTypeName() const
    {
        return getTypeName(getType());
    }


    std::string Tag::getTypeName(uint8_t type)
    {
        switch (type)
        {
            case TAG_END:
                return "End";

            case TAG_BYTE:
                return "Byte";

            case TAG_INT:
                return "Int";

            case TAG_SHORT:
                return "Short";

            case TAG_LONG:
                return "Long";

            case TAG_FLOAT:
                return "Float";

            case TAG_DOUBLE:
                return "Double";

            case TAG_BYTE_ARRAY:
                return "Byte Array";

            case TAG_STRING:
                return "String";

            case TAG_LIST:
                return "List";

            case TAG_COMPOUND:
                return "Compound";

            case TAG_INT_ARRAY:
                return "Int Array";

            default:
                return "Unknown";
        }
    }


    ByteArray Tag::toByteArray() const
    {
        ByteArray ret;
        int16_t length = _name.length();

        ret.push_back(getType());

        // Turn the 2 byte length into an array of two 1 byte length
        int8_t *flip = reinterpret_cast<int8_t *>(&length);

        for (int i = 1; i >= 0; --i)
            ret.push_back(flip[i]);

        for (size_t i = 0; i < _name.length(); ++i)
            ret.push_back(_name[i]);
        
        return ret;
    }


    std::string Tag::toString() const
    {
        return "TAG" + (_name.empty() ? "" : "(\"" + _name + "\")");
    }
}
