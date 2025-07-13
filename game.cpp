#include "objects/commons.h"

int main()
{
    std::locale::global(std::locale("")); //making special characters work

    ITF::itf_tile da_test;
    da_test.test();

    std::locale::global(std::locale::classic()); //clears the special characters interpreter
    return 0;
}