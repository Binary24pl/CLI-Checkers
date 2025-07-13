#include "objects/commons.h"

int main()
{
    std::locale::global(std::locale("")); //making special characters work

    ITF::itf_tile* test1 = nullptr;
    test1 = new itf_tile(1,1);
    test1->init();

    delete test1;

    std::locale::global(std::locale::classic()); //clears the special characters interpreter
    return 0;
}