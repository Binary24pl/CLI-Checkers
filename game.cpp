#include "objects/commons.h"

int main()
{
    std::locale::global(std::locale("")); //making special characters work

    ITF::itf_query_elm<int>* test;
    test = new ITF::itf_query_elm<int>;
    test->set_input(1);

    ITF::itf_input_range<int> test_range;
    test_range.args_amn = 4;
    test_range.containter = new int[test_range.args_amn];
    
    test_range.containter[0] = 1;
    test_range.containter[1] = 2;
    test_range.containter[3] = 3;
    test_range.containter[4] = 4;

    test_range.what_range = ITF_RANGE_FROM_TO;
    test->set_range(test_range);
    std::cout << test->validate() << std::endl;

    test_range.what_range = ITF_RANGE_BEYOND_FROM_TO;
    test->set_range(test_range);
    std::cout << test->validate() << std::endl;

    test_range.what_range = ITF_RANGE_IS_IN;
    test->set_range(test_range);
    std::cout << test->validate() << std::endl;

    test_range.what_range = ITF_RANGE_IS_NOT_IN;
    test->set_range(test_range);
    std::cout << test->validate() << std::endl;

    std::locale::global(std::locale::classic()); //clears the special characters interpreter
    return 0;
}