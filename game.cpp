#include "objects/commons.h"

int main()
{
    std::locale::global(std::locale("")); //making special characters work

    itf_input_range<int> range_test;
    range_test.args_len = 4;
    range_test.args_type = ITF_RANGE_FROM_TO;
    range_test.args = new int[range_test.args_len];
    range_test.args[0] = 1;
    range_test.args[1] = 5;
    range_test.args[2] = 10;
    range_test.args[3] = 15;

    const int len = 5;
    itf_query_master** test = new itf_query_master*[len];
    test[0] = new itf_query_element<int>;

    common_passer(range_test, test[0], &ITF::itf_query_master::set_range);
    common_passer(1, test[0], &ITF::itf_query_master::assign_val);
    for(int i = 1; i < len; i++) {
        test[i] = new itf_query_element<int>(test[0]);
        int to_add = i * 5;

        common_passer(to_add, test[i], &ITF::itf_query_master::assign_val);
    }

    delete[] range_test.args;
    for(int del = 0; del < len; del++) delete (itf_query_element<int>*)test[del];
    delete[] test;
    std::locale::global(std::locale::classic()); //clears the special characters interpreter
    return 0;
}