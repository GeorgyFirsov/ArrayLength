/*******************************************************
 *  ArrayLength is a function that calculates
 *  length of C-style array of any type.
 *
 *  Its work based on C++ type inference
 *  If we pass an array to function by reference, its
 *  type will be T(&)[Length]
 *  We use this fact here
 *
 *  Prameters:
 *      - <unnamed> - static array
 *
 *  Return value:
 *      - length of static array
 *******************************************************
 *  Author: Firsov Georgy
 *  Contact: gfirsov007@gmail.com
 *  Date: 25.07.2019
 *******************************************************/
#pragma once

#include <cstdio> // for size_t

template<typename T, size_t Length>
constexpr size_t ArrayLength(const T(&)[Length]);
