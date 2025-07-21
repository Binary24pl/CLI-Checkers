#include "objects/commons.h"

int main()
{
    std::locale::global(std::locale("")); //making special characters work

    int tst = 2;
    void (*func_ptr)(void*&) = test;;
    common_passer<int>(tst, func_ptr);

    std::locale::global(std::locale::classic()); //clears the special characters interpreter
    return 0;
}