#include "objects/commons.h"

int main()
{
    std::locale::global(std::locale("")); //making special characters work

    ITF::itf_tile* test = nullptr;
    test = new itf_tile(1,1);
    test->init();

    delete test;

    std::locale::global(std::locale::classic()); //clears the special characters interpreter
    return 0;
}