/******************************************************************************
 *
 *  TAG_Double implementation (tag_double.cc)
 *  ---
 *  Created: 02.02.2011 16:08:45
 *  Author:  Lukas Niederbremer
 *
 ******************************************************************************/
#include "tag_double.h"

namespace nbt
{
    TagDouble::TagDouble(const std::string &name, const double &value) : Tag(name)
    {
        _value = value;
    }


    TagDouble::TagDouble(const TagDouble &t) : Tag(t.getName())
    {
        _value = t.getValue();
    }

    
    double TagDouble::getValue() const
    {
        return _value;
    }


    void TagDouble::setValue(const double &value)
    {
        _value = value;
    }


    uint8_t TagDouble::getType() const
    {
        return TAG_DOUBLE;
    }


    ByteArray TagDouble::toByteArray()
    {
        ByteArray ret = Tag::toByteArray();

        uint8_t *split = reinterpret_cast<uint8_t *>(&_value);

        for (int i = 7; i >= 0; --i)
            ret.push_back(split[i]);

        return ret;
    }


    std::string TagDouble::toString()
    {
        std::stringstream ret;
        
        ret << "TAG_Double";
        
        if (!_name.empty())
            ret << "(\"" << _name << "\")";
        
        ret << ": " << _value;

        return ret.str();
    }

    Tag *TagDouble::clone() const
    {
        return new TagDouble(_name, _value);
    }
}
