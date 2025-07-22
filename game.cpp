#include "objects/commons.h"

int main()
{
    std::locale::global(std::locale("")); //making special characters work
    
    itf_query_master** test = new itf_query_master*[2];
    test[0] = new itf_query_element<int>;
    common_passer(5, test[0], &ITF::itf_query_master::assign_val);
    test[1] = new itf_query_element<int>(test[0]);

    delete test[0];
    delete test[1];
    delete[] test;

    std::locale::global(std::locale::classic()); //clears the special characters interpreter
    return 0;
}