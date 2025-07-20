template<typename input_type>
void itf_query_elm<input_type>::set_range(const itf_input_range<input_type>& range)
{
    if(this->range_of_input != nullptr) {
        itf_input_range<input_type>* temp = this->range_of_input;
        this->range_of_input = nullptr;

        delete[] temp->containter;
        delete temp;
    }

    this->range_of_input = new itf_input_range<input_type>;
    
    this->range_of_input->what_range = range.what_range;
    this->range_of_input->args_amn = range.args_amn;

    this->range_of_input->containter = new input_type[this->range_of_input->args_amn];
    for(int trans = 0; trans < range.args_amn; trans++) {
        range_of_input->containter[trans] = range.containter[trans];
    }
}