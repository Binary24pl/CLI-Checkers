#include "objects/commons.h"

int main()
{
    std::locale::global(std::locale("")); //making special characters work

    ITF::itf_query_elm<int>* test;
    test = new ITF::itf_query_elm<int>;

    const int length = 3;
    ITF::itf_input_range<int> passer;
    passer.containter = new int[length];
    passer.args_amn = length;
    passer.what_range = ITF_RANGE_FROM_TO;

    passer.containter[0] = 1;
    passer.containter[1] = 3;
    passer.containter[2] = 9;

    test->set_range(passer);
    test->set_range(passer);
    test->set_range(passer);
    test->set_range(passer);
    test->set_range(passer);

    delete test;
    delete[] passer.containter;

    std::locale::global(std::locale::classic()); //clears the special characters interpreter
    return 0;
}