/******************************************************************************
 *
 *  TAG_Byte implementation (tag_byte.cc)
 *  ---
 *  Created: 02.02.2011 03:53:42
 *  Author:  Lukas Niederbremer
 *
 ******************************************************************************/
#include "tag_byte.h"

namespace nbt
{
    TagByte::TagByte(const std::string &name, const int8_t &value) : Tag(name)
    {
        _value = value;
    }


    TagByte::TagByte(const TagByte &t) : Tag(t.getName())
    {
        _value = t.getValue();
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


    ByteArray TagByte::toByteArray()
    {
        ByteArray ret = Tag::toByteArray();

        ret.push_back(_value);

        return ret;
    }


    std::string TagByte::toString()
    {
        std::stringstream ret;

        ret << "TAG_Byte";

        if (!_name.empty())
            ret << "(\"" << _name << "\")";
        
        ret << ": " << _value;

        return ret.str();
    }

    Tag* TagByte::clone() const
    {
        return new TagByte(_name, _value);
    }
}
