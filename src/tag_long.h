/******************************************************************************
 *
 *  TAG_Long definition (tag_long.h)
 *  ---
 *  Created: 02.02.2011 15:55:33
 *  Author:  Lukas Niederbremer
 *
 ******************************************************************************/
#ifndef TAG_LONG_H
#define TAG_LONG_H

#include <string>
#include <sstream>

#include "tag.h"

namespace nbt
{
    class TagLong : public Tag
    {
        public:
            TagLong(const std::string &name, const int64_t &value = 0);
            TagLong(const TagLong &t);

            int64_t getValue() const;
            void setValue(const int64_t &value);

            virtual uint8_t getType() const;
            virtual ByteArray toByteArray() const;
            virtual std::string toString() const;

            virtual Tag *clone() const;

        protected:
            int64_t _value;
    };
}

#endif
