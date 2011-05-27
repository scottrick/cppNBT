/******************************************************************************
 *
 *  TAG_List implementation (tag_list.cc)
 *  ---
 *  Created: 02.02.2011 21:24:36
 *  Author:  Lukas Niederbremer
 *
 ******************************************************************************/
#include "tag_list.h"

namespace nbt
{
    TagList::TagList(const uint8_t &type,
                     const std::string &name,
                     const std::vector<Tag *> &value)
        : Tag(name)
    {
        _childType = type;
        _value = value;
    }


    TagList::TagList(const TagList &t) : Tag(t.getName())
    {
        _childType = t.getChildType();
        _value = t.getValue();
    }


    TagList::~TagList()
    {
        // DEVILS BE GONE
    }


    std::vector<Tag *> TagList::getValue() const
    {
        return _value;
    }


    void TagList::setValue(const std::vector<Tag *> &value)
    {
        _value = value;
    }


    uint8_t TagList::getChildType() const
    {
        return _childType;
    }


    void TagList::setChildType(const uint8_t &value)
    {
        _childType = value;
        clear();
    }


    void TagList::append(Tag *value)
    {
        if (value->getType() == _childType)
            _value.push_back(value);

    }


    void TagList::append(const std::vector<Tag *> &values)
    {
        for (size_t i = 0; i < values.size(); ++i)
            if (values[i]->getType() == _childType)
                _value.push_back(values[i]);
    }


    void TagList::removeFirst()
    {
        if (_value.size() > 0)
        {
            _value.erase(_value.begin());
        }
    }


    void TagList::removeLast()
    {
        if (_value.size() > 0)
            _value.erase(_value.end());
    }


    void TagList::removeAll(Tag *tag)
    {
        // TODO
    }


    void TagList::removeOne(Tag *tag)
    {
        for (size_t i = 0; i < _value.size(); ++i)
        {
            if (_value[i] == tag)
            {
                _value.erase(_value.begin() + i);
                break;
            }
        }
    }


    void TagList::removeAt(const int &i)
    {
        if (_value.size() > 0)
        {
            _value.erase(_value.begin() + i);
        }
    }


    void TagList::clear()
    {
        /*for (size_t i = 0; i < _value.size(); ++i)
            delete _value[i];*/

        _value.clear();
    }


    Tag *TagList::at(const int &i)
    {
        if (_value.size() > 0)
            return _value.at(i);
        else
            throw EmptyListException();
    }


    Tag *TagList::back()
    {
        if (_value.size() > 0)
            return _value.back();
        else
            throw EmptyListException();
    }


    Tag *TagList::front()
    {
        if (_value.size() > 0)
            return _value.front();
        else
            throw EmptyListException();
    }


    bool TagList::contains(Tag *tag) const
    {
        for (size_t i = 0; i < _value.size(); ++i)
            if (_value[i] == tag)
                return true;

        return false;
    }


    size_t TagList::size() const
    {
        return _value.size();
    }


    uint8_t TagList::getType() const
    {
        return TAG_LIST;
    }


    ByteArray TagList::toByteArray()
    {
        ByteArray ret = Tag::toByteArray();

        ret.push_back(getChildType());

        int32_t len = _value.size();
        uint8_t *split = reinterpret_cast<uint8_t *>(&len);

        for (int i = 3; i >= 0; --i)
            ret.push_back(split[i]);

        for (size_t i = 0; i < _value.size(); ++i)
        {
            ByteArray tmp = _value[i]->toByteArray();
            uint8_t len_parts[2];

            len_parts[0] = tmp.at(2);
            len_parts[1] = tmp.at(1);

            int16_t *len = reinterpret_cast<int16_t*>(len_parts);

            tmp.erase(tmp.begin(), tmp.begin() + 3 + *len);

            for (size_t j = 0; j < tmp.size(); ++j)
                ret.push_back(tmp[j]);
        }

        return ret;
    }


    std::string TagList::toString()
    {
        std::stringstream ret;
        
        ret << "TAG_List";

        if (!_name.empty())
            ret << "(\"" << _name << "\")";

        ret << ": " << _value.size() << " entries of type " 
                    << getTypeName(_childType) << std::endl 
                    << "{" << std::endl;

        for (size_t i = 0; i < _value.size(); ++i)
            ret << "  "
                << string_replace(_value[i]->toString(), "\n", "\n  ")
                << std::endl;

        ret << "}";

        return ret.str();
    }
}
