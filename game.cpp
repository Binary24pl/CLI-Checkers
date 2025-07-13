#include "objects/commons.h"

int main()
{
    std::locale::global(std::locale("")); //making special characters work

    ITF::itf_tile* test;
    test = new ITF::itf_tile(4,4);
    
    test->init();
    std::cout << test->tile_buffer.size() << std::endl;

    test->paint_fill(ITF_C_WHITE, ITF_HIGH_INTEN);
    test->create_build();

    delete test;

    std::locale::global(std::locale::classic()); //clears the special characters interpreter
    return 0;
}