/******************************************************************************
 *
 *  TAG_Float implementation (tag_float.cc)
 *  ---
 *  Created: 02.02.2011 16:02:11
 *  Author:  Lukas Niederbremer
 *
 ******************************************************************************/
#include "tag_float.h"

namespace nbt
{
    TagFloat::TagFloat(const std::string &name, const float &value) : Tag(name)
    {
        _value = value;
    }


    TagFloat::TagFloat(const TagFloat &t) : Tag(t.getName())
    {
        _value = t.getValue();
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


    ByteArray TagFloat::toByteArray()
    {
        ByteArray ret = Tag::toByteArray();

        uint8_t *split = reinterpret_cast<uint8_t *>(&_value);

        for (int i = 3; i >= 0; --i)
            ret.push_back(split[i]);

        return ret;
    }


    std::string TagFloat::toString()
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
