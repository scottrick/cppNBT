/******************************************************************************
 *
 *   (tag_end.cc)
 *  ---
 *  Created: 02.02.2011 03:40:42
 *  Author:  Lukas Niederbremer
 *
 ******************************************************************************/
#include "tag_end.h"

namespace nbt
{
    TagEnd::TagEnd() : Tag("")
    {
        // Do nothing
    }


    TagEnd::TagEnd(const TagEnd &t) : Tag(t.getName())
    {
        // Do nothing
    }

    
    uint8_t TagEnd::getType() const
    {
        return TAG_END;
    }


    std::string TagEnd::toString()
    {
        return "TAG_End";
    }
}
