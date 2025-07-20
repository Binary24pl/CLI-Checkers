#include "objects/commons.h"

int main()
{
    std::locale::global(std::locale("")); //making special characters work

    LOGIC::logic_node* test;
    test = new LOGIC::logic_node(LOGIC_NODE_NONE);

    test->connected_from(1,1);
    test->connected_from(1,1);
    test->connected_from(1,1);
    test->connected_from(1,1);
    test->connected_from(1,1);

    delete test;

    std::locale::global(std::locale::classic()); //clears the special characters interpreter
    return 0;
}