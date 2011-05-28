/******************************************************************************
 *
 *  TAG_Double definition (tag_double.h)
 *  ---
 *  Created: 02.02.2011 16:08:30
 *  Author:  Lukas Niederbremer
 *
 ******************************************************************************/
#ifndef TAG_DOUBLE_H
#define TAG_DOUBLE_H

#include <string>
#include <sstream>

#include "tag.h"

namespace nbt
{
    class TagDouble : public Tag
    {
        public:
            TagDouble(const std::string &name, const double &value = 0);
            TagDouble(const TagDouble &t);

            double getValue() const;
            void setValue(const double &value);

            virtual uint8_t getType() const;
            virtual ByteArray toByteArray() const;
            virtual std::string toString() const;

            virtual Tag *clone() const;

        protected:
            double _value;
    };
}

#endif
