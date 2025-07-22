#include "objects/commons.h"

int main()
{
    std::locale::global(std::locale("")); //making special characters work
    
    itf_query_master** test = new itf_query_master*[2];

    ITF::itf_input_range<int> range_main;
    range_main.args_len = 1;
    range_main.args_type = ITF_RANGE_IS_IN;
    range_main.args = new int[1];
    range_main.args[0] = 5;

    test[0] = new itf_query_element<int>;
    common_passer(5, test[0], &ITF::itf_query_master::assign_val);
    common_passer(range_main, test[0], &ITF::itf_query_master::set_range);
    test[1] = new itf_query_element<int>(test[0]);

    delete test[0];
    delete test[1];
    delete[] test;
    delete[] range_main.args;

    std::locale::global(std::locale::classic()); //clears the special characters interpreter
    return 0;
}