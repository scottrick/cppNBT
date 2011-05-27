/******************************************************************************
 *
 *  TAG_Int definition (tag_int.h)
 *  ---
 *  Created: 02.02.2011 15:43:08
 *  Author:  Lukas Niederbremer
 *
 ******************************************************************************/
#ifndef TAG_INT_H
#define TAG_INT_H

#include <string>
#include <sstream>

#include "tag.h"

namespace nbt
{
    class TagInt : public Tag
    {
        public:
            TagInt(const std::string &name, const int32_t &value = 0);
            TagInt(const TagInt &t);

            int32_t getValue() const;
            void setValue(const int32_t &value);

            virtual uint8_t getType() const;
            virtual ByteArray toByteArray();
            virtual std::string toString();

        protected:
            int32_t _value;
    };
}

#endif
