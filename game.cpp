#include "objects/commons.h"

int main() {
    std::locale::global(std::locale("")); //making special characters work

    GAM::gam_mainloop gamemaster(10,10);
    gamemaster.init();

    bool controler = true;
    while (controler)
    {
        gamemaster.run_loop(controler);
    }
    

    std::locale::global(std::locale::classic());

    return 0;
}