#include "objects/commons.h"

int main()
{
    std::locale::global(std::locale("")); //making special characters work

    ITF::itf_question* test = new ITF::itf_question;
    test->start_new_question(3);
    test->start_new_question(1);
    test->start_new_question(5);
    test->start_new_question(3);

    for(int sup_test = 0; sup_test < 3; sup_test++) {
        for(int sub_test = 0; sub_test < 3; sub_test++) {
            ITF::itf_input_whatami our_type = (ITF::itf_input_whatami)sup_test;
            test->build_into_question(our_type, sub_test);
        }
    }

    delete test;
    
    std::locale::global(std::locale::classic()); //clears the special characters interpreter
    return 0;
}