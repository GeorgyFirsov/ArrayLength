# Utilites

This repo contains various utilites for common computer usage and C++ programming.

## Table of contents

- [ArrayLength](#ArrayLength)
- [is_convertible and is_convertible_v](#is_convertible-and-is_convertible_v)
- [ThrowsException and ThrowsAnyException](#ThrowsException-and-ThrowsAnyException)
- [LookUp](#LookUp)

### ArrayLength
`ArrayLength` is a function, that calculates length of C-style static array in compile time. Requires at least C++11.

It was created to use with old API in modern C++, in such moments, when you can not replace C-style array with std::vector, std::string or std::array.

Example:

```cpp
int aiFirst[] = { 1, 2, 3, 4, 5};

std::cout << ArrayLength(aiFirst); // prints: 5

int aiSecond[ArrayLength(aiFirst)];
assert( ArrayLength(aiFirst) == ArrayLength(aiSecond) );
assert( ArrayLength(aiSecond) == 5 );

constexpr auto ulLength = ArrayLength(aiFirst);
assert( ulLength == 5 );
```

### is_convertible and is_convertible_v

`is_convertible` is a class, that contains variable value, which is true, when and only when first type is implicitly convertible to second one (same types are allowed). `is_convertible_v` is just a simpler way to use class above.

Example:

```cpp
std::cout << std::boolalpha;

std::cout << is_convertible<short, int>::value;       // prints: true
std::cout << is_convertible_v<short, int>;            // prints: true
std::cout << is_convertible_v<int, std::vector<int>>; // prints: false
                                                      // std::vector(int) is explicit constructor
```

### ThrowsException and ThrowsAnyException

These two functions return true, if callable object (parameter) throws an exception. Here better to show an example:

```cpp
void foo() noexcept { }
void bar() { throw std::runtime_error("Error"); }
void baz(int t, std::string str) { if (!t) throw std::logic_error("Error"); }

std::cout << std::boolalpha;

std::cout << ThrowsException<std::runtime_error>(foo);          // prints: false

std::cout << ThrowsException<std::runtime_error>(bar);          // prints: true
std::cout << ThrowsException<std::exception>(bar);              // prints: true
std::cout << ThrowsException<std::logic_error>(bar);            // prints: false

std::cout << ThrowsException<std::logic_error>(baz, 1, "Text"); // prints: false
std::cout << ThrowsException<std::logic_error>(baz, 0, "Text"); // prints: true

std::cout << ThrowsAnyException(foo);                           // prints: false
std::cout << ThrowsAnyException(bar);                           // prints: true
std::cout << ThrowsAnyException(baz, 1, "Text");                // prints: false
std::cout << ThrowsAnyException(baz, 0, "Text");                // prints: true
```

### LookUp

This simple python script can help you to find files with specific line inside. For instance, you need to find all 
files with boolean variable bFlag. So you can run following command:
```bash
python LookUp.py dir=my_dir "bool bFlag"
```

Full usage of this utilite:
```
python LookUp.py [dir=<search_dir>] [mode=<mode>] string1 [string2 [string3 ...]]
        
Searches strings string1, string2, etc. in all files in specified directory search_dir
        
Parameters:
    - dir - directory with files (by default - directory with script)
    - mode - type of search:
        0 - search in subdirectories too (default)
        1 - search only in current directory
```
