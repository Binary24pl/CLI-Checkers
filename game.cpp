#include "objects/commons.h"

int main()
{
    std::locale::global(std::locale("")); //making special characters work

    ITF::itf_tile* test;
    const int sqr = 8;
    test = new ITF::itf_tile(sqr, sqr);
    
    test->init();

    test->paint_fill(ITF_C_WHITE, ITF_HIGH_INTEN);

    test->create_build();
    test->create_buffer();

    for(int i = 0; i < test->tile_buffer.size(); i++) {
        std::cout << test->tile_buffer[i] << std::endl;
    }

    delete test;

    std::locale::global(std::locale::classic()); //clears the special characters interpreter
    return 0;
}