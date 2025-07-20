#include "objects/commons.h"

int main()
{
    std::locale::global(std::locale("")); //making special characters work

    const int len = 4;

    ITF::itf_query** test;
    test = new ITF::itf_query*[len];

    for(int i = 0; i < len; i++) {
        if(i % 2 == 0) {
            test[i] = new ITF::itf_query_elm<std::string>;
        } else {
            test[i] = new ITF::itf_query_elm<int>;
        }
    }
    
    for(int i = 0; i < len; i++) {
        delete test[i];
    }
    delete[] test;

    std::locale::global(std::locale::classic()); //clears the special characters interpreter
    return 0;
}