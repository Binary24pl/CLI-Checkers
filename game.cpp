#include "objects/commons.h"

int main()
{
    std::locale::global(std::locale("")); //making special characters work

    ITF::itf_question* test = new itf_question();
    
    delete test;
    std::locale::global(std::locale::classic()); //clears the special characters interpreter
    return 0;
}