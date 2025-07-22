#include "objects/commons.h"

int main()
{
    std::locale::global(std::locale("")); //making special characters work

    ITF::itf_query_master** master = new ITF::itf_query_master*[1];
    master[0] = new ITF::itf_query_element<int>;

    void (ITF::itf_query_master::*func_ptr)(void*&) = &ITF::itf_query_master::test;
        

    delete master[0];
    delete[] master;

    std::locale::global(std::locale::classic()); //clears the special characters interpreter
    return 0;
}