/******************************************************************************
 *
 *  Basic Tag definition (tag.h)
 *  ---
 *  Definition of the basic Tag object.
 *
 *  Created: 02.02.2011 02:45:09
 *  Author:  Lukas Niederbremer
 *
 ******************************************************************************/
#ifndef TAG_H
#define TAG_H

#include <vector>
#include <string>

#include <stdint.h> // int8_t, int16_t, ...

namespace nbt
{
    typedef std::vector<unsigned char> ByteArray;

    enum
    {
        TAG_END        = 0,
        TAG_BYTE       = 1,
        TAG_SHORT      = 2,
        TAG_INT        = 3,
        TAG_LONG       = 4,
        TAG_FLOAT      = 5,
        TAG_DOUBLE     = 6,
        TAG_BYTE_ARRAY = 7,
        TAG_STRING     = 8,
        TAG_LIST       = 9,
        TAG_COMPOUND   = 10
    };

    class Tag
    {
        public:
            // Constructors
            Tag(const std::string &name);
            Tag(const Tag &t);

            virtual ~Tag();

            // Get and set name
            std::string getName() const;
            void setName(const std::string &name);

            // Get type name and ID
            std::string getTypeName() const;
            static std::string getTypeName(uint8_t type);

            virtual uint8_t getType() const;
            virtual ByteArray toByteArray() const;
            virtual std::string toString() const;

            virtual Tag* clone() const = 0;

        protected:
            std::string _name;
    };
}

#endif
