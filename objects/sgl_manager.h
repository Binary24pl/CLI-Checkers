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

            this->regions[region] = new sgl_signal[this->depths[region]];
        }
    }
}

std::vector<sgl_data_type> sgl_manager::show_pattern()
{
    std::vector<sgl_data_type> to_return;


    for(int i = 0; i < this->local_pattern.size(); i++) {
        const sgl_data_type our_taken = this->local_pattern[i].our_type;

        to_return.push_back(our_taken);
    }

    return to_return;
}

void sgl_manager::build_from_pattern()
{
    if(this->local_pattern.size() != this->depths[this->identity]) return;

    if(this->regions[this->identity] == nullptr) return;

    for(int check = 0; check < this->local_pattern.size(); check++) {
        if(this->local_pattern[check].our_type == SGL_DTTP_WRONG) return;
    }

    for(int make = 0; make < this->depths[this->identity]; make++) {
        this->local_pattern[make].typer(this->regions[this->identity][make]);
    }
}