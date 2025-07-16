#include "objects/commons.h"

int main()
{
    std::locale::global(std::locale("")); //making special characters work

    ITF::itf_show_pallette();

    std::vector<ITF::itf_tile*> preload_content;
    ITF::itf_preload_content(preload_content);

    std::cout << std::endl;
    for(int show = 0; show < ITF_COUNT_IDX; show++)
    {
        itf_tile* working_tile = preload_content[show];
        for(int buf_show = 0; buf_show < working_tile->tile_buffer.size(); buf_show++) {
            std::cout << working_tile->tile_buffer[buf_show] << std::endl;
        }
        std::cout << std::endl;
    }

    ITF::itf_clean_content(preload_content);
    std::locale::global(std::locale::classic()); //clears the special characters interpreter
    return 0;
}