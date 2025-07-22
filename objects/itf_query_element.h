template<typename input_type>
void itf_query_element<input_type>::assign_val(void*& val)
{
    input_type* caster = (input_type*)val;
    const input_type casted = *caster;

    this->ntv_assign_val(casted);
}

template<typename input_type>
void itf_query_element<input_type>::set_range(void*& range)
{
    itf_input_range<input_type>* caster = (itf_input_range<input_type>*)range;
    const itf_input_range<input_type> casted = *caster;

    this->ntv_set_range(casted);
}

template<typename input_type>
bool itf_query_element<input_type>::validate()
{}

template<typename input_type>
void itf_query_element<input_type>::ntv_assign_val(const input_type& val)
{
    this->local_val = val;

    std::cout << this->local_val << std::endl;
}

template<typename input_type>
void itf_query_element<input_type>::ntv_set_range(const itf_input_range<input_type>& range)
{
    if((range.args_type == ITF_RANGE_FROM_TO || range.args_type == ITF_RANGE_FROM_TO) && range.args_len % 2 != 0) {
        std::cout << "Da number is odd :(" << std::endl;
        return;
    }

    if(this->local_range != nullptr) {
        itf_input_range<input_type>* temp_holder = this->local_range;

        this->local_range = new itf_input_range<input_type>;
        
        delete[] temp_holder->args;
        delete temp_holder;
    } else {
        this->local_range = new itf_input_range<input_type>;
    }

    this->local_range->args_len = range.args_len;
    this->local_range->args_type = range.args_type;

    const int len = range.args_len;
    this->local_range->args = new input_type[len];
    for(int copy = 0; copy < len; copy++) {
        this->local_range->args[copy] = range.args[copy];
    }
}