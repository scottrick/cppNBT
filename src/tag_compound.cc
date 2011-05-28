/******************************************************************************
 *
 *  TAG_Compound implementation (tag_compound.cc)
 *  ---
 *  Created: 03.02.2011 00:17:29
 *  Author:  Lukas Niederbremer
 *
 ******************************************************************************/
#include "tag_compound.h"

namespace nbt
{
    TagCompound::TagCompound(const std::string &name,
                             const std::list<Tag *> &value)
        : Tag(name)
    {
        std::list<Tag *>::const_iterator i;

        for (i = value.begin(); i != value.end(); ++i)
            insert(**i);
    }


    TagCompound::TagCompound(const TagCompound &t) : Tag(t.getName())
    {
        std::vector<Tag *>::const_iterator i;
        std::vector<Tag *> v = t.getValues();

        for (i = v.begin(); i != v.end(); ++i)
            insert(**i);
    }


    TagCompound::~TagCompound()
    {
        std::list<Tag *>::iterator it;

        for (it = _value.begin(); it != _value.end(); ++it)
            delete *it;
    }


    std::list<Tag *> TagCompound::getValue() const
    {
        return _value;
    }


    void TagCompound::setValue(const std::list<Tag *> value)
    {
        std::list<Tag *>::const_iterator i;
        for (i = value.begin(); i != value.end(); ++i)
            insert(**i);
    }

    void TagCompound::insert(const Tag &tag)
    {
        _value.push_back(tag.clone());
    }

    void TagCompound::remove(const std::string &name)
    {
        // TODO: Throw exception if name not known
        std::list<Tag *>::iterator it;
        for (it = _value.begin(); it != _value.end(); ++it)
        {
            if ((*it)->getName() == name)
            {
                delete *it;
                _value.erase(it);

                break;
            }
        }
    }

    std::vector<std::string> TagCompound::getKeys() const
    {
        std::vector<std::string> ret;
        std::list<Tag *>::const_iterator it;

        for (it = _value.begin(); it != _value.end(); ++it)
            ret.push_back((*it)->getName());

        return ret;
    }


    std::vector<Tag *> TagCompound::getValues() const
    {
        std::vector<Tag *> ret;
        std::list<Tag *>::const_iterator it;

        for (it = _value.begin(); it != _value.end(); ++it)
            ret.push_back(*it);

        return ret;
    }


    Tag *TagCompound::getValueAt(const std::string &key) const
    {
        std::list<Tag *>::const_iterator it;

        for (it = _value.begin(); it != _value.end(); ++it)
            if ((*it)->getName() == key)
                return *it;

        throw KeyNotFoundException();
    }


    uint8_t TagCompound::getType() const
    {
        return TAG_COMPOUND;
    }


    ByteArray TagCompound::toByteArray() const
    {
        ByteArray ret = Tag::toByteArray();
        std::list<Tag *>::const_iterator it;

        for(it = _value.begin(); it != _value.end(); ++it)
        {
            ByteArray tmp = (*it)->toByteArray();

            for (size_t i = 0; i < tmp.size(); ++i)
                ret.push_back(tmp[i]);
        }

        ret.push_back((char)TAG_END);

        return ret;
    }


    std::string TagCompound::toString() const
    {
        std::stringstream ret;
        std::list<Tag *>::const_iterator it;

        ret << "TAG_Compound";

        if (!_name.empty())
            ret << "(\"" << _name << "\")";

        ret << ": " << _value.size() << " entries" << std::endl
            << "{" << std::endl;

        for (it = _value.begin(); it != _value.end(); ++it)
            ret << "  " 
                << string_replace((*it)->toString(), "\n", "\n  ") 
                << std::endl;

        ret << "}";

        return ret.str();
    }

    Tag *TagCompound::clone() const
    {
        TagCompound *ret = new TagCompound(_name);

        std::list<Tag *>::const_iterator t;
        for (t = _value.begin(); t != _value.end(); ++t)
            ret->insert(**t);

        return ret;
    }

    TagCompound &TagCompound::operator<<(const Tag &tag)
    {
        insert(tag);

        return *this;
    }
}
