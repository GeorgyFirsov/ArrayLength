# Utilites

This repository contains various utility functions, that can help you with C++ programming.

### ArrayLength
Funcion that calculates length of C-style array in compile time. Requires at least C++11

It was created to use with old API in modern C++
In some cases where yo9u can not change C-style array with std::vector, std::string or std::array

It allows you to write this:

```cpp
int aiFirst[] = { 1, 2, 3, 4, 5};

std::cout << ArrayLength(aiFirst); // 5

int aiSecond[ArrayLength(aiFirst)];
assert( ArrayLength(aiFirst) == ArrayLength(aiSecond) );
assert( ArrayLength(aiSecond) == 5 );

constexpr auto ulLength = ArrayLength(aiFirst); // 5
int aiThird[ulLength];
assert( ArrayLength(aiFirst) == ArrayLength(aiThird) );
assert( ArrayLength(aiThird) == 5 );
```
