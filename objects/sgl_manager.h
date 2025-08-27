void sgl_manager::declare_region(const int& amount) {
    this->depths[this->identity] = amount;
}

void sgl_manager::show_region_counts()
{
    for(int i = 0; i < SGL_AUTH_COUNT; i++) {
        std::cout << this->depths[i] << std::endl;
    }
}