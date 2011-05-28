/******************************************************************************
 *
 *  TAG_Compound definition (tag_compound.h)
 *  ---
 *  Created: 03.02.2011 00:17:45
 *  Author:  Lukas Niederbremer
 *
 ******************************************************************************/
#ifndef TAG_COMPOUND_H
#define TAB_COMPOUND_H

#include <sstream>
#include <string>
#include <list>
#include <stdexcept>
#include <functional>

#include "tag.h"
#include "util.h"

namespace nbt
{
    class KeyNotFoundException : public std::runtime_error
    {
        public:
            KeyNotFoundException() 
                : std::runtime_error("key not found in compound") {}
    };


    class TagCompound : public Tag
    {
        public:
            TagCompound(const std::string &name = "",
                        const std::list<Tag *> &value  = 
                            std::list<Tag *>());
            TagCompound(const TagCompound &t);

            ~TagCompound();

            std::list<Tag *> getValue() const;
            void setValue(std::list<Tag *> value);

            void insert(const Tag &tag);
            void remove(const std::string &name);

            std::vector<std::string> getKeys() const;
            std::vector<Tag *> getValues() const;
            Tag *getValueAt(const std::string &key) const;

            Tag *operator[](const std::string &key) const;
            TagCompound &operator<<(const Tag &tag);

            virtual uint8_t getType() const;
            virtual ByteArray toByteArray();
            virtual std::string toString();

            virtual Tag *clone() const;

        protected:
            std::list<Tag *> _value;
    };
}

#endif
