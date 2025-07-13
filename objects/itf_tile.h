void itf_tile::init()
{
    if(this->height == -1 && this->width == -1) {
        std::cout << "Height and width need to be even numbers" << std::endl;
        return;
    }

    this->tile_build = new itf_pixels*[this->height];
    for(int rows = 0; rows < this->height; rows++) {
        this->tile_build[rows] = new itf_pixels[this->width];
        for(int columns = 0; columns < this->width; columns++) {
            this->tile_build[rows][columns].used = false;
        }
    }
}