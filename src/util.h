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

#include <string>

std::string string_replace(const std::string &string, 
                           const std::string &find,
                           const std::string &replace);

#endif
