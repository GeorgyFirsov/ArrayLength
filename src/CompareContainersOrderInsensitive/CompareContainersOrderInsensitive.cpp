/*******************************************************
 *  CompareContainersOrderInsensitive implementation
 *******************************************************
 *  Author: Firsov Georgy
 *  Contact: gfirsov007@gmail.com
 *  Date: 27.08.2019
 *******************************************************/

#include "CompareContainersOrderInsensitive.h"

#include <algorithm>
#include <type_traits>
#include <set>
#include <vector>
#include <iterator>

namespace
{

#pragma region Utils

constexpr auto unsigned_long_max = 0xFFFFFFFFUL;
constexpr auto crc32_magic_number = 0xEDB88320UL;

unsigned long Crc32(const void* pData, size_t cbLength)
{
    auto buf = reinterpret_cast<const unsigned char*>(pData);
  
    static std::vector<unsigned long> crc_table;

    if(crc_table.empty())
    {
        crc_table.resize(256, 0);
    
        for (auto i = 0; i < 256; i++)
        {
            unsigned long value = i;
            for (auto j = 0; j < 8; j++)
                value = value & 1 ? (value >> 1) ^ crc32_magic_number : value >> 1;
        
            crc_table[i] = value;
        }
    }
      
    auto crc = unsigned_long_max;
    
    while (cbLength--)
        crc = crc_table[(crc ^ *buf++) & 0xFF] ^ (crc >> 8);
    
    return crc ^ unsigned_long_max;
};

#pragma endregion


//
// Implementation for simple types (int, char, pointers, etc.)
//
template<
    typename T,
    template<typename, typename> class ContainerT,
    template<typename> class Allocator
>
bool CompareContainersOrderInsensitiveImpl(const ContainerT<T, Allocator<T>>& first, 
                                           const ContainerT<T, Allocator<T>>& second,
                                           std::true_type /* bIsSimple */)
{
    auto Identity = [](const T& element) { return element; };
    
    std::set<T> firstSet, secondSet;
    
    std::transform(
        first.cbegin(), first.cend(),
        std::inserter(firstSet, firstSet.begin()),
        Identity
    );
    
    std::transform(
        second.cbegin(), second.cend(),
        std::inserter(secondSet, secondSet.begin()),
        Identity
    );
    
    return firstSet == secondSet;
}


//
// Implementation for POD (but non-simple built-in) types
//
template<
    typename T,
    template<typename, typename> class ContainerT,
    template<typename> class Allocator
>
bool CompareContainersOrderInsensitiveImpl(const ContainerT<T, Allocator<T>>& first, 
                                           const ContainerT<T, Allocator<T>>& second,
                                           std::false_type /* bIsSimple */)
{
    //
    // To compare structs I use Crc32 hashes of instances.
    //
    auto Hash = [](const T& element) { return Crc32(&element, sizeof(T)); };
    
    std::set<unsigned long> firstSet, secondSet;
    
    std::transform(
        first.cbegin(), first.cend(),
        std::inserter(firstSet, firstSet.begin()),
        Hash
    );
    
    std::transform(
        second.cbegin(), second.cend(),
        std::inserter(secondSet, secondSet.begin()),
        Hash
    );
    
    return firstSet == secondSet;
}

}

//  --------------------------- Implementation ---------------------------

template<
    typename T,
    template<typename, typename> class ContainerT,
    template<typename> class Allocator = std::allocator
>
bool CompareContainersOrderInsensitive(const ContainerT<T, Allocator<T>>& first, 
                                       const ContainerT<T, Allocator<T>>& second)
{
    static_assert(
        std::is_pod<T>::value, 
        "Template parameter T in CompareContainersOrderInsensitive should be POD"
    );

    //
    // Fast checks
    //
    if(first.empty() && second.empty()) return true;
    if(first.size() != second.size()) return false;
    
    return CompareContainersOrderInsensitiveImpl(
        first, 
        second, 
        std::integral_constant<
            bool,
            std::is_arithmetic<T>::value || std::is_pointer<T>::value
        >()
    );
}