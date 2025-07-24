#include "objects/commons.h"

int main()
{
    std::locale::global(std::locale("")); //making special characters work

    ITF::itf_question* test = new ITF::itf_question;
    test->start_new_question(3);
    test->start_new_question(1);
    test->start_new_question(5);
    test->start_new_question(3);

    itf_input_range<std::string> test_range;
    test_range.args_len = 4;
    test_range.args_type = ITF_RANGE_IS_IN;

    test_range.args = new std::string[test_range.args_len];

    for(int idx = 0; idx < test_range.args_len; idx++) {
        test_range.args[idx] = "test";
    }

    for(int sup_test = 0; sup_test < 3; sup_test++) {
        for(int sub_test = 0; sub_test < 3; sub_test++) {
            ITF::itf_input_whatami our_type = (ITF::itf_input_whatami)sup_test;
            test->build_into_question(our_type, sub_test);
            test->give_element_range<std::string>(test_range, 0);
        }
    }

    delete test;
    delete[] test_range.args;
    
    std::locale::global(std::locale::classic()); //clears the special characters interpreter
    return 0;
}