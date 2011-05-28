/******************************************************************************
 *
 *  TAG_List definition (tag_list.h)
 *  ---
 *  Created: 02.02.2011 21:24:19
 *  Author:  Lukas Niederbremer
 *
 ******************************************************************************/
#ifndef TAG_LIST_H
#define TAG_LIST_H

#include <string>
#include <sstream>
#include <stdexcept>

#include "tag.h"
#include "util.h"

namespace nbt
{
    class EmptyListException : public std::runtime_error
    {
        public:
            EmptyListException()
                : std::runtime_error("list is empty") {}
    };

    class TagList : public Tag
    {
        public:
            TagList(const uint8_t &type,
                    const std::string &name, 
                    const std::vector<Tag *> &value = std::vector<Tag *>());
            TagList(const TagList &t);

            ~TagList();

            std::vector<Tag *> getValue() const;
            void setValue(const std::vector<Tag *> &value);

            uint8_t getChildType() const;
            void setChildType(const uint8_t &value);

            void append(const Tag &value);

            void removeFirst();
            void removeLast();
            void remove(Tag *tag);
            void remove(size_t i);
            void clear();

            Tag *at(size_t i) const;
            Tag *back() const;
            Tag *front() const;

            Tag *operator[](size_t index) const;
            TagList &operator<<(const Tag &tag);

            size_t size() const;                

            virtual uint8_t getType() const;
            virtual ByteArray toByteArray();
            virtual std::string toString();

            virtual Tag *clone() const;

        protected:
            uint8_t _childType;
            std::vector<Tag *> _value;

    };
}

#endif
