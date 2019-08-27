/*******************************************************
 *  ArrayLength is a function that calculates
 *  length of C-style array of any type.
 *
 *  Its work based on C++ type inference
 *  If we pass an array to function by reference, its
 *  type will be T(&)[Length]
 *  We use this fact here
 *******************************************************
 *  Author: Firsov Georgy
 *  Contact: gfirsov007@gmail.com
 *  Date: 25.07.2019
 *******************************************************/
#pragma once

template<typename T, size_t Length>
constexpr auto ArrayLength(const T(&)[Length]);
