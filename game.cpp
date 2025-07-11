#include "objects/commons.h"

int main()
{
    std::locale::global(std::locale("")); //making special characters work


    test foo;
    foo.test.push_back(1);

    std::locale::global(std::locale::classic()); //clears the special characters interpreter
    return 0;
}