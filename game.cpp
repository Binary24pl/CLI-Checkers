#include "objects/commons.h"

int main()
{
    std::locale::global(std::locale("")); //making special characters work

    ITF::itf_query_elm<int>* test;

    const int total = 2;
    int* la_range;
    la_range = new int[total];

    la_range[0] = 0;
    la_range[1] = 1;


    test->provide_input(10);
    test->set_range(la_range, ITF_RANGE_FROM_TO, total);
    test->set_range(la_range, ITF_RANGE_FROM_TO, total);
    test->set_range(la_range, ITF_RANGE_FROM_TO, total);
    test->set_range(la_range, ITF_RANGE_FROM_TO, total);

    delete test;
    delete la_range;

    std::locale::global(std::locale::classic()); //clears the special characters interpreter
    return 0;
}