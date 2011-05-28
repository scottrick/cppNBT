/******************************************************************************
 *
 *  Utilites (util.h)
 *  ---
 *  Created: 03.02.2011 02:55:25
 *  Author:  Lukas Niederbremer
 *
 ******************************************************************************/
#ifndef UTIL_H
#define UTIL_H

#include <stdint.h>
#include <string>
#include <iostream>

std::string string_replace(const std::string &string, 
                           const std::string &find,
                           const std::string &replace);


template <typename T>
void flipBytes(T &val)
{
    size_t size = sizeof(val);
    T retval;

    uint8_t *src = reinterpret_cast<uint8_t *>(&val);
    uint8_t *dst = reinterpret_cast<uint8_t *>(&retval);

    for (size_t i = 0; i < size; ++i)
        dst[i] = src[size - (i + 1)];

    val = retval;
}

bool is_big_endian();

#endif
