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