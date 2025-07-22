#include "objects/commons.h"

int main()
{
    std::locale::global(std::locale("")); //making special characters work

    ITF::itf_query_master** master = new ITF::itf_query_master*[1];
    master[0] = new ITF::itf_query_element<std::string>;
    
    std::string test = "hello world";
    common_passer(test, master[0], &ITF::itf_query_master::assign_val);

    delete master[0];
    delete[] master;

    std::locale::global(std::locale::classic()); //clears the special characters interpreter
    return 0;
}