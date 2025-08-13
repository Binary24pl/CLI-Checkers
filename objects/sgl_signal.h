bool sgl_signal::self_validate() {
    if(this->cleaner == nullptr) {
        return false;
    }

    return true;
}