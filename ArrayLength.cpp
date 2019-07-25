/*******************************************************
 *
 *  ArrayLength is a function that calculates
 *  length of C-style array of any type.
 *
 *  T - type of elements in array
 *  Length - length of this array
 *
 *  Its work based on C++ type inference
 *  If we pass an array to function by reference, its
 *  type will be T(&)[Length]
 *  We use this fact here
 *
 *******************************************************
 *
 *  Author: Firsov Georgy
 *  Contact: gfirsov007@gmail.com
 *  Date: 25.07.2019
 *
 *******************************************************/
template<typename T, size_t Length>
constexpr auto ArrayLength(const T(&)[Length])
{
    return Length;
}



// 
// It calculates size in compile time, so you can do
// like that
//
int aiFirst[] = { 1, 2, 3, 4, 5 };
int aiSecond[ArrayLength(aiFirst)]; // It works

assert( ArrayLength(aiFirst) == ArrayLength(aiSecond) );
assert( ArrayLength(aiSecond) == 5 );

//
// But prefer using std::array<T, Len> in modern C++
// This function makes your work with OLD API easier
//
