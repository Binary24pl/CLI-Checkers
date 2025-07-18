void itf_board::init() {
    if(this->board_height == -1 || this->board_width == -1) {
        return;
    }

    itf_preload_content(this->pre_gen_content);

    this->buffer_size = this->pre_gen_content[ITF_IDX_EMPTY]->tile_buffer.size();
    std::cout << buffer_size << std::endl;
}