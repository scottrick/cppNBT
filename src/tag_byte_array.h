/******************************************************************************
 *
 *  TAG_Byte_Array definition (tag_byte_array.h)
 *  ---
 *  Created: 02.02.2011 16:19:49
 *  Author:  Lukas Niederbremer
 *
 ******************************************************************************/
#ifndef TAG_BYTE_ARRAY_H
#define TAG_BYTE_ARRAY_H

#include <string>
#include <sstream>

#include "tag.h"

namespace nbt
{
    class TagByteArray : public Tag
    {
        public:
            TagByteArray(const std::string &name,
                         const ByteArray &value = ByteArray());
            TagByteArray(const TagByteArray &t);

            ByteArray getValue() const;
            void setValue(const ByteArray &value);

            virtual uint8_t getType() const;
            virtual ByteArray toByteArray() const;
            virtual std::string toString() const;

            virtual Tag *clone() const;

        protected:
            ByteArray _value;
    };
}

#endif
