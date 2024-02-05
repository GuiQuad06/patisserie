// utility.h
// SPDX-FileCopyrightText: 2024 GuiQuad06 guillaume.cuadrado@gmail.com
// SPDX-License-Identifier: GPL-2.0-or-later

#ifndef UTILITY_H
#define UTILITY_H

#include <string>

/**
* Remove the trailing spaces
*
* @param input (reference to a standard string)
* @return a reference to a standard string (without trailing spaces)
*/
static inline std::string& remove_trailing_spaces(std::string& input)
{
    size_t pos = input.find_last_not_of(' ');
    if (pos != std::string::npos)
        input.erase(pos + 1);
    else
        input.clear();  // input is all spaces
    return input;
}

#endif // UTILITY_H
