#include "objects/commons.h"

int main()
{
    std::locale::global(std::locale("")); //making special characters work
    
    //8 allocs 6 frees

    itf_query_master** test = new itf_query_master*[2]; // alloc id: 1

    ITF::itf_input_range<int> range_main;
    range_main.args_len = 1;
    range_main.args_type = ITF_RANGE_IS_IN;
    range_main.args = new int[1]; //alloc id: 5
    range_main.args[0] = 5;

    test[0] = new itf_query_element<int>; // alloc id: 2
    common_passer(5, test[0], &ITF::itf_query_master::assign_val);
    common_passer(range_main, test[0], &ITF::itf_query_master::set_range);
    test[1] = new itf_query_element<int>; // alloc id: 3
    common_passer(range_main, test[1], &ITF::itf_query_master::set_range);

    delete (itf_query_element<int>*)test[0]; //de_alloc id: 2
    delete (itf_query_element<int>*)test[1]; // de_alloc id: 3
    
    delete[] test; //de_alloc id: 1
    delete[] range_main.args;

    std::locale::global(std::locale::classic()); //clears the special characters interpreter
    return 0;
}