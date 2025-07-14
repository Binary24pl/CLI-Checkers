#include "objects/commons.h"

int main()
{
    std::locale::global(std::locale("")); //making special characters work

    ITF::itf_tile* test;
    const int sqr = 8;
    test = new ITF::itf_tile(sqr, sqr);
    
    test->init();

    test->paint_fill(ITF_C_WHITE, ITF_HIGH_INTEN);

    test->paint_pixel(ITF_C_RED, ITF_LOW_INTEN);
    test->draw_pencil.on_hght = 7;
    test->draw_pencil.on_wdth = 7;
    test->paint_pixel(ITF_C_GREEN, ITF_LOW_INTEN);
    test->create_new_layer(ITF_MOVE_PEN);

    test->paint_line(ITF_C_BLUE, ITF_HIGH_INTEN, ITF_D_UP, 7);
    test->paint_line(ITF_C_RED, ITF_HIGH_INTEN, ITF_D_LEFT, 7);

    test->draw_pencil.on_layer = 0;
    test->draw_pencil.on_wdth = 0;
    test->paint_line(ITF_C_RED, ITF_LOW_INTEN, ITF_D_RIGHT, 8);

    test->draw_pencil.on_hght = 0;
    test->draw_pencil.on_wdth = 2;
    test->paint_line(ITF_C_BLACK, ITF_HIGH_INTEN, ITF_D_DOWN, 4);

    test->create_build();
    test->create_buffer();
    test->create_buffer();
    test->create_buffer();

    for(int i = 0; i < test->tile_buffer.size(); i++) {
        std::cout << test->tile_buffer[i] << std::endl;
    }

    delete test;

    std::locale::global(std::locale::classic()); //clears the special characters interpreter
    return 0;
}