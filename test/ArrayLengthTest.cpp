#include <cassert>

#include "../src/cpp/ArrayLength/ArrayLength.h"

bool RunTests()
{
    bool bSuccess = true;

    int TestArray1[10];
    int TestArray2[] = {1, 2, 3, 4};

    if (ArrayLength(TestArray1) != 10) bSuccess = false;
    if (ArrayLength(TestArray2) !=  4) bSuccess = false;

    int TestArray3[ArrayLength(TestArray2)];

    if (ArrayLength(TestArray3) !=  4) bSuccess = false;

    return bSuccess;
}


int main()
{
    assert(RunTests());
}