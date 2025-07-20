template<typename input_type>
bool itf_query_elm<input_type>::check_range_from_to()
{
    for(int check = 0; check < this->range_of_input->args_amn; check += 2) {
        if(this->input_val >= this->range_of_input->containter[check] && this->input_val <= this->range_of_input->containter[check + 1]) return true;
    }

    return false;
}

template<typename input_type>
bool itf_query_elm<input_type>::check_range_beyond()
{
    for(int check = 0; check < this->range_of_input->args_amn; check += 2) {
        if(this->input_val >= this->range_of_input->containter[check] && this->input_val <= this->range_of_input->containter[check + 1]) return false;
    }

    return true;
}

template<typename input_type>
bool itf_query_elm<input_type>::check_range_is_in()
{
    for(int check = 0; check < this->range_of_input->args_amn; check++) {
        if(this->input_val == this->range_of_input->containter[check]) return true;
    }

    return false;
}

template<typename input_type>
bool itf_query_elm<input_type>::check_range_is_not_in()
{
    for(int check = 0; check < this->range_of_input->args_amn; check++) {
        if(this->input_val == this->range_of_input->containter[check]) return false;
    }

    return true;
}