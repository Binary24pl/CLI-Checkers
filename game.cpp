#include "objects/commons.h"

int main()
{
    std::locale::global(std::locale("")); //making special characters work

    ITF::itf_query_master** master = new ITF::itf_query_master*[1];
    master[0] = new ITF::itf_query_element<std::string>;
    
    ITF::itf_input_range<std::string> test_range;
    test_range.args_len = 5;
    test_range.args_type = ITF_RANGE_FROM_TO;
    test_range.args = new std::string[test_range.args_len];

    common_passer(test_range, master[0], &ITF::itf_query_master::set_range);
    common_passer(test_range, master[0], &ITF::itf_query_master::set_range);
    common_passer(test_range, master[0], &ITF::itf_query_master::set_range);

    delete master[0];
    delete[] master;

    std::locale::global(std::locale::classic()); //clears the special characters interpreter
    return 0;
}