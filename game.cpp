#include "objects/commons.h"

int main()
{
    std::locale::global(std::locale("")); //making special characters work

    ITF::itf_tile* test;
    test = new ITF::itf_tile(4,4);
    
    test->init();
    std::cout << test->draw_pencil.on_layer << std::endl;

    test->paint_fill(ITF_C_WHITE, ITF_HIGH_INTEN);

    delete test;

    std::locale::global(std::locale::classic()); //clears the special characters interpreter
    return 0;
}