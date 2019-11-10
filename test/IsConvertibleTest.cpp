#include <cassert>
#include <vector>

#include "../src/cpp/IsConvertible/IsConvertible.h"

bool RunTests()
{
    bool bSuccess = true;

    if (!is_convertible<int, int>::value) bSuccess = false;
    if (!is_convertible_v<int, int>) bSuccess = false;

    if (!is_convertible_v<short, int>) bSuccess = false;
    if (!is_convertible_v<int, short>) bSuccess = false;

    if (!is_convertible_v<int, std::vector<int>>) bSuccess = false;

    return bSuccess;
}


int main()
{
    assert(RunTests());
}