#include <cassert>
#include <string>
#include <stdexcept>

#include "../src/cpp/ThrowsException/ThrowsException.h"

void foo() noexcept { }
void bar() { throw std::runtime_error("Error"); }
void baz(int t, std::string str) { if (!t) throw std::logic_error("Error"); }

bool RunTests()
{
    bool bSuccess = true;

    if (!ThrowsException<std::runtime_error>(foo)) bSuccess = false;

    if (!ThrowsException<std::runtime_error>(bar)) bSuccess = false;
    if (!ThrowsException<std::exception>(bar)) bSuccess = false;
    if ( ThrowsException<std::logic_error>(bar)) bSuccess = false;

    if ( ThrowsException<std::logic_error>(baz, 1, "Text")) bSuccess = false;
    if (!ThrowsException<std::logic_error>(baz, 0, "Text")) bSuccess = false;

    if ( ThrowsAnyException(foo)) bSuccess = false;
    if (!ThrowsAnyException(bar)) bSuccess = false;
    if ( ThrowsAnyException(baz, 1, "Text")) bSuccess = false;
    if (!ThrowsAnyException(baz, 0, "Text")) bSuccess = false;

    return bSuccess;
}


int main()
{
    assert(RunTests());
}