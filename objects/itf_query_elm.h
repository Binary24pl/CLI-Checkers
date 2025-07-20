template<typename input_type>
void itf_query_elm<input_type>::set_range(const itf_input_range<input_type>& range)
{
    if((range.what_range == ITF_RANGE_BEYOND_FROM_TO || range.what_range == ITF_RANGE_FROM_TO) && range.args_amn % 2 != 0) {
        return;
    }

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

template<typename input_type>
void itf_query_elm<input_type>::set_input(const input_type& val)
{
    this->input_val = val;
}

template<typename input_type>
bool itf_query_elm<input_type>::validate()
{
    if(this->range_of_input != nullptr) {
        //soon
    }
    return true;
}