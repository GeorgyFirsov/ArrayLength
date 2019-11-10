/*******************************************************
 *  CompareContainersOrderInsensitive is a template
 *  function that compares two containers with POD
 *  elements. Order of elements in container doesn't
 *  matter.
 *
 *  Here I use tag dispatch idiom to provide more
 *  efficient algorithm for pointers and simple
 *  arithmetic types.
 *
 *  Prameters:
 *      - first - const reference to the first container
 *      - second - const reference to the second container
 *
 *  Return value:
 *      - true - containers have same elements
 *      - false - containers contain different elements
 *******************************************************
 *  Author: Firsov Georgy
 *  Contact: gfirsov007@gmail.com
 *  Date: 10.11.2019
 *******************************************************/
#pragma once

#include <memory>

template<
    typename T,
    template<typename, typename> class ContainerT,
    template<typename> class Allocator = std::allocator
>
bool CompareContainersOrderInsensitive(const ContainerT<T, Allocator<T>>& first, 
                                       const ContainerT<T, Allocator<T>>& second);