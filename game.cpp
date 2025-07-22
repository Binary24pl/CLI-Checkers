#include "objects/commons.h"

int main()
{
    std::locale::global(std::locale("")); //making special characters work

    ITF::itf_query_master** master = new ITF::itf_query_master*[1];
    master[0] = new ITF::itf_query_element<int>;

    common_passer(5, master[0], &ITF::itf_query_master::assign_val);

    ITF::itf_input_range<int> test_range;
    test_range.args_len = 4;
    test_range.args = new int[test_range.args_len];
    
    test_range.args[0] = 1;
    test_range.args[1] = 4;
    test_range.args[2] = 5;
    test_range.args[3] = 10;

    std::cout << master[0]->validate() << std::endl;

    test_range.args_type = ITF_RANGE_FROM_TO;
    common_passer(test_range, master[0], &ITF::itf_query_master::set_range);
    std::cout << master[0]->validate() << std::endl;

    test_range.args_type = ITF_RANGE_BEYOND;
    common_passer(test_range, master[0], &ITF::itf_query_master::set_range);
    std::cout << master[0]->validate() << std::endl;

    test_range.args_type = ITF_RANGE_IS_IN;
    common_passer(test_range, master[0], &ITF::itf_query_master::set_range);
    std::cout << master[0]->validate() << std::endl;

    test_range.args_type = ITF_RANGE_IS_NOT_IN;
    common_passer(test_range, master[0], &ITF::itf_query_master::set_range);
    std::cout << master[0]->validate() << std::endl;

    delete master[0];
    delete[] master;

    std::locale::global(std::locale::classic()); //clears the special characters interpreter
    return 0;
}