/******************************************************************************
 *
 *  TAG_Short definition (tag_short.h)
 *  ---
 *  Created: 02.02.2011 04:07:14
 *  Author:  Lukas Niederbremer
 *
 ******************************************************************************/
#ifndef TAG_SHORT_H
#define TAG_SHORT_H

#include <string>
#include <sstream>

#include "tag.h"

namespace nbt
{
    class TagShort : public Tag
    {
        public:
            TagShort(const std::string &name, const int16_t &value = 0);
            TagShort(const TagShort &t);

            int16_t getValue() const;
            void setValue(const int16_t &value);

            virtual uint8_t getType() const;
            virtual ByteArray toByteArray();
            virtual std::string toString();

        protected:
            int16_t _value;
    };
}

#endif
