void sgl_manager::declare_region(const int& amount) {
    this->depths[this->identity] = amount;
}

void sgl_manager::make_regions_depths()
{
    if(this->identity != SGL_AUTH_GOD) {
        return;
    }

    for(int region = 0; region < SGL_AUTH_COUNT; region++) {
        if(this->depths[region] > 0) {
            if(this->regions[region] != nullptr) {
                delete[] this->regions[region];
            }

            std::cout << "hi :3" << std::endl;

            this->regions[region] = new sgl_signal[this->depths[region]];
        }
    }
}