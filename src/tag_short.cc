/******************************************************************************
 *
 *  TAG_Short implementation (tag_short.cc)
 *  ---
 *  Created: 02.02.2011 04:07:27
 *  Author:  Lukas Niederbremer
 *
 ******************************************************************************/
#include "tag_short.h"

namespace nbt
{
    TagShort::TagShort(const std::string &name, const int16_t &value) : Tag(name)
    {
        _value = value;
    }


    TagShort::TagShort(const TagShort &t) : Tag(t.getName())
    {
        _value = t.getValue();
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


    ByteArray TagShort::toByteArray()
    {
        ByteArray ret = Tag::toByteArray();

        uint8_t *split = reinterpret_cast<uint8_t *>(&_value);

        for (int i = 1; i >= 0; --i)
            ret.push_back(split[i]);

        return ret;
    }


    std::string TagShort::toString()
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
