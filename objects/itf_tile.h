void itf_tile::init()
{
    if(this->height == -1 && this->width == -1) {
        return;
    }

    this->tile_build = new itf_pixels*[this->height];
    for(int rows = 0; rows < this->height; rows++) {
        this->tile_build[rows] = new itf_pixels[this->width];
        for(int columns = 0; columns < this->width; columns++) {
            this->tile_build[rows][columns].used = false;
        }
    }

    this->create_new_layer(ITF_MOVE_PEN);
}

void itf_tile::create_new_layer(bool move_pen = false)
{
    itf_pixels** to_push;

    to_push = new itf_pixels*[this->height];
    for(int crt_rws = 0; crt_rws < this->height; crt_rws++) {
        to_push[crt_rws] = new itf_pixels[this->width];
        for(int crt_clm = 0; crt_clm < this->width; crt_clm++) {
            to_push[crt_rws][crt_clm].used = false;
        }
    }

    this->draw_layers.push_back(to_push);

    //moving pen to last upper layer if user wishes so
    if(move_pen) {
        int last_layer = this->draw_layers.size() - 1;
        this->draw_pencil.on_layer = last_layer;
    }
}