void itf_board::init() {
    if(this->board_height == -1 || this->board_width == -1) {
        return;
    }

    itf_preload_content(this->pre_gen_content);

    this->buffer_size = this->pre_gen_content[ITF_IDX_EMPTY]->tile_buffer.size();

    this->state_visual = new itf_preload_idx*[this->board_height];
    for(int sv = 0; sv < this->board_height; sv++) {
        this->state_visual[sv] = new itf_preload_idx[this->board_width];
    }
}

void itf_board::show_visual_state() {
    std::vector<std::string> local_bfr;
    for(int start_vals = 0; start_vals < this->buffer_size; start_vals++) local_bfr.push_back("");

    for(int on_hght = 0; on_hght < this->board_height; on_hght++) {
        for(int rst_bfr = 0; rst_bfr < this->buffer_size; rst_bfr++) local_bfr[rst_bfr] = "";

        for(int on_wdth = 0; on_wdth < this->board_width; on_wdth++) {
            const std::vector<std::string> other_buffer = this->pre_gen_content[this->state_visual[on_hght][on_wdth]]->tile_buffer;

            for(int add_bfr = 0; add_bfr < this->buffer_size; add_bfr++) local_bfr[add_bfr] += other_buffer[add_bfr];
        }

        for(int shw_bfr = 0; shw_bfr < this->buffer_size; shw_bfr++) {
            std::cout << local_bfr[shw_bfr] << std::endl;
        }
    }
}

void itf_board::test() {
    for(int on_hght = 0; on_hght < this->board_height; on_hght++) {
        for(int on_wdth = 0; on_wdth < this->board_width; on_wdth++) {
            if(on_hght % 2 == on_wdth % 2) {
                this->state_visual[on_hght][on_wdth] = ITF_IDX_EMPTY;
            } else {
                this->state_visual[on_hght][on_wdth] = ITF_IDX_NON_PLAYABLE;
            }
        }
    }
}