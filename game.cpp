#include "objects/commons.h"

int main()
{
    std::locale::global(std::locale("")); //making special characters work

    ITF::itf_query_elm<std::string>* test;
    test = new ITF::itf_query_elm<std::string>;

    delete test;

    std::locale::global(std::locale::classic()); //clears the special characters interpreter
    return 0;
}