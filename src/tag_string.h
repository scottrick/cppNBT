/******************************************************************************
 *
 *  TAG_String definition (tag_string.h)
 *  ---
 *  Created: 02.02.2011 17:52:37
 *  Author:  Lukas Niederbremer
 *
 ******************************************************************************/
#ifndef TAG_STRING_H
#define TAG_STRING_H

#include <string>
#include <sstream>

#include "tag.h"

namespace nbt
{
    class TagString : public Tag
    {
        public:
            TagString(const std::string &name, const std::string &value = "");
            TagString(const TagString &t);

            std::string getValue() const;
            void setValue(const std::string &value);

            virtual uint8_t getType() const;
            virtual ByteArray toByteArray();
            virtual std::string toString();

        protected:
            std::string _value;
    };
}


#endif
