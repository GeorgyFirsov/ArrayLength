/*******************************************************
 *  ArrayLength implementation
 *******************************************************
 *  Author: Firsov Georgy
 *  Contact: gfirsov007@gmail.com
 *  Date: 25.07.2019
 *******************************************************/

#include "ArrayLength.h"

template<typename T, size_t Length>
constexpr size_t ArrayLength(const T(&)[Length])
{
    return Length;
}
