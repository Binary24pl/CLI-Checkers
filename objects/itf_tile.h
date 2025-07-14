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

void itf_tile::create_build()
{
    int layers = this->draw_layers.size();
    for(int rd_lyr = 0; rd_lyr < layers; rd_lyr++) {
        itf_pixels** working_layer;
        working_layer = this->draw_layers[rd_lyr];

        for(int rd_hgt = 0; rd_hgt < this->height; rd_hgt++) {
            for(int rd_wdt = 0; rd_wdt < this->width; rd_wdt++) {
                if(working_layer[rd_hgt][rd_wdt].used) {
                    this->tile_build[rd_hgt][rd_wdt].color = working_layer[rd_hgt][rd_wdt].color;
                    this->tile_build[rd_hgt][rd_wdt].intensity = working_layer[rd_hgt][rd_wdt].intensity;
                    this->tile_build[rd_hgt][rd_wdt].used = true;
                }
            }
        }
    }
}

void itf_tile::create_buffer()
{
    const int hght_char = this->height / 2;

    for(int rst = 0; rst < hght_char; rst++) this->tile_buffer[rst] = "";

    for(int ch_hgt = 0; ch_hgt < hght_char; ch_hgt++) {
        for(int ch_wdt = 0; ch_wdt < this->width; ch_wdt++) {
            itf_text_pallete val_colors;
            
            val_colors.bg_color = ITF_C_BLACK;
            val_colors.fg_color = ITF_C_BLACK;
            val_colors.bg_inten = ITF_LOW_INTEN;
            val_colors.bg_inten = ITF_LOW_INTEN;

            const int sup_hgt = ch_hgt * 2;
            const int sub_hgt = (ch_hgt * 2) + 1;

            std::string product = ITF_BHB;

            if(this->tile_build[sup_hgt][ch_wdt].used) {
                val_colors.bg_color = this->tile_build[sup_hgt][ch_wdt].color;
                val_colors.bg_inten = this->tile_build[sup_hgt][ch_wdt].intensity;
            }

            if(this->tile_build[sub_hgt][ch_wdt].used) {
                val_colors.fg_color = this->tile_build[sub_hgt][ch_wdt].color;
                val_colors.fg_inten = this->tile_build[sub_hgt][ch_wdt].intensity;
            }

            product = itf_give_color(product, val_colors);
            this->tile_buffer[ch_hgt] += product;
        }
    }
}

void itf_tile::paint_fill(const itf_colors color, const bool intensity)
{
    if(this->draw_pencil.on_layer < 0 || this->draw_pencil.on_layer >= this->draw_layers.size()) {
        return;
    }

    itf_pixels** working_layer;
    working_layer = this->draw_layers[this->draw_pencil.on_layer];
    // extracting the layer

    for(int chn_hgt = 0; chn_hgt < this->height; chn_hgt++) {
        for(int chn_wdt = 0; chn_wdt < this->width; chn_wdt++) {
            working_layer[chn_hgt][chn_wdt].used = true;
            working_layer[chn_hgt][chn_wdt].color = color;
            working_layer[chn_hgt][chn_wdt].intensity = intensity;
        }
    }
}

void itf_tile::paint_pixel(const itf_colors color, const bool intensity)
{
    if(this->draw_pencil.on_layer < 0 || this->draw_pencil.on_layer >= this->draw_layers.size()) {
        return;
    }

    itf_pixels** wokring_layer;
    wokring_layer = this->draw_layers[this->draw_pencil.on_layer];

    if(this->draw_pencil.on_hght < 0 || this->draw_pencil.on_wdth < 0 || this->draw_pencil.on_hght >= this->height || this->draw_pencil.on_wdth >= this->width) {
        return; // out of bounds
    }

    wokring_layer[this->draw_pencil.on_hght][this->draw_pencil.on_wdth].color = color;
    wokring_layer[this->draw_pencil.on_hght][this->draw_pencil.on_wdth].intensity = intensity;
    wokring_layer[this->draw_pencil.on_hght][this->draw_pencil.on_wdth].used = true;
}

void itf_tile::paint_line(const itf_colors color, const bool intensity, const itf_lines_drct direction, const int size)
{
    if(this->draw_pencil.on_layer < 0 || this->draw_pencil.on_layer >= this->draw_layers.size()) {
        return;
    }

    itf_pixels** working_layer;
    working_layer = this->draw_layers[this->draw_pencil.on_layer];

    if(this->draw_pencil.on_hght < 0 || this->draw_pencil.on_wdth < 0 || this->draw_pencil.on_hght >= this->height || this->draw_pencil.on_wdth >= this->width) {
        return; // out of bounds
    }

    int diff; // it will be used for calculations and cotrol checks
    if(direction == ITF_D_UP || direction == ITF_D_DOWN) {
        diff = this->draw_pencil.on_hght;
        
        if(direction == ITF_D_UP) {
            diff -= size;
            diff += 1;
        } else if(direction == ITF_D_DOWN) {
            diff += size;
            diff -= 1;
        }

        if(diff < 0 || diff >= this->height) {
            return;
        }

        if(diff == this->draw_pencil.on_hght) {
            this->paint_pixel(color, intensity);
            return;
        }
    } else if(direction == ITF_D_LEFT || direction == ITF_D_RIGHT) {
        diff = this->draw_pencil.on_wdth;

        if(direction == ITF_D_LEFT) {
            diff -= size;
            diff += 1;
        } else if(direction == ITF_D_RIGHT) {
            diff += size;
            diff -= 1;
        }

        if(diff < 0 || diff >= this->width) {
            return;
        }

        if(diff == this->draw_pencil.on_wdth) {
            this->paint_pixel(color, intensity);
            return;
        }
    }

    //finally drawing some stuff

    if(direction == ITF_D_UP || direction == ITF_D_DOWN) {
        int high, low;

        //I wont be doing nested if's, I will just do one for loop for high and low values
        if(diff > this->draw_pencil.on_hght) {
            high = diff;
            low = this->draw_pencil.on_hght;
        } else {
            high = this->draw_pencil.on_hght;
            low = diff;
        }

        for(int chn_hgt = low; chn_hgt <= high; chn_hgt++) {
            working_layer[chn_hgt][this->draw_pencil.on_wdth].color = color;
            working_layer[chn_hgt][this->draw_pencil.on_wdth].intensity = intensity;
            working_layer[chn_hgt][this->draw_pencil.on_wdth].used = true;
        }
    } else if(direction == ITF_D_LEFT || direction == ITF_D_RIGHT) {  // Fixed the typo here
        int high, low;

        if(diff > this->draw_pencil.on_wdth) {
            high = diff;
            low = this->draw_pencil.on_wdth;
        } else {
            high = this->draw_pencil.on_wdth;
            low = diff;
        }

        for(int chn_wdt = low; chn_wdt <= high; chn_wdt++) {
            working_layer[this->draw_pencil.on_hght][chn_wdt].color = color;
            working_layer[this->draw_pencil.on_hght][chn_wdt].intensity = intensity;
            working_layer[this->draw_pencil.on_hght][chn_wdt].used = true;
        }
    }
}