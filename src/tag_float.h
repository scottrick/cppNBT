/******************************************************************************
 *
 *  TAG_Float definition (tag_float.h)
 *  ---
 *  Created: 02.02.2011 16:01:45
 *  Author:  Lukas Niederbremer
 *
 ******************************************************************************/
#ifndef TAG_FLOAT_H
#define TAG_FLOAT_H

#include <string>
#include <sstream>

#include "tag.h"

namespace nbt
{
    class TagFloat : public Tag
    {
        public:
            TagFloat(const std::string &name, const float &value = 0);
            TagFloat(const TagFloat &t);

            float getValue() const;
            void setValue(const float &value);

            virtual uint8_t getType() const;
            virtual ByteArray toByteArray();
            virtual std::string toString();

        protected:
            float _value;
    };
}

#endif
