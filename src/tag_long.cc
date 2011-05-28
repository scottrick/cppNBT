/******************************************************************************
 *
 *  TAG_Long implementation (tag_long.cc)
 *  ---
 *  Created: 02.02.2011 15:55:55
 *  Author:  Lukas Niederbremer
 *
 ******************************************************************************/
#include "tag_long.h"

namespace nbt
{
    TagLong::TagLong(const std::string &name, const int64_t &value) : Tag(name)
    {
        _value = value;
    }


    TagLong::TagLong(const TagLong &t) : Tag(t.getName())
    {
        _value = t.getValue();
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
