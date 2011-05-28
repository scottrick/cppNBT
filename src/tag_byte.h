/******************************************************************************
 *
 *  TAG_Byte definition (tag_byte.h)
 *  ---
 *  Created: 02.02.2011 03:53:40
 *  Author:  Lukas Niederbremer
 *
 ******************************************************************************/
#ifndef TAG_BYTE_H
#define TAG_BYTE_H

#include <string>
#include <sstream>

#include "tag.h"

namespace nbt
{
    class TagByte : public Tag
    {
        public:
            TagByte(const std::string &name, const int8_t &value = 0);
            TagByte(const TagByte &t);

            int8_t getValue() const;
            void setValue(const int8_t &value);

            virtual uint8_t getType() const;
            virtual ByteArray toByteArray() const;
            virtual std::string toString() const;

            virtual Tag *clone() const;

        protected:
            int8_t _value;
    };
}

#endif
