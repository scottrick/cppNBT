/******************************************************************************
 *
 *  TAG_End definition (tag_end.h)
 *  ---
 *  Created: 02.02.2011 03:40:49
 *  Author:  Lukas Niederbremer
 *
 ******************************************************************************/
#ifndef TAG_END_H
#define TAG_END_H

#include <string>

#include "tag.h"

namespace nbt
{
    class TagEnd : public Tag
    {
        public:
            TagEnd();
            TagEnd(const TagEnd &t);

            virtual uint8_t getType() const;
            virtual std::string toString() const;

            virtual Tag *clone() const;

    };
}

#endif
