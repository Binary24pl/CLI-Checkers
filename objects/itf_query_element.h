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
{
    if(this->identity == ITF_INPUT_ERROR) {
        return false;
    }

    if(this->local_range != nullptr) {
        const itf_inrange_type our_type = this->local_range->args_type;

        switch (our_type)
        {
        case ITF_RANGE_FROM_TO:
            return this->range_from_to();
            break;
        
        case ITF_RANGE_BEYOND:
            return this->range_beyond();
            break;
        
        case ITF_RANGE_IS_IN:
            return this->range_is_in();
            break;
        
        case ITF_RANGE_IS_NOT_IN:
            return this->range_not_in();
            break;

        default:
            break;
        }
    }

    return true;
}

template<typename input_type>
void itf_query_element<input_type>::ntv_assign_val(const input_type& val)
{
    this->local_val = val;
}

template<typename input_type>
void itf_query_element<input_type>::ntv_set_range(const itf_input_range<input_type>& range)
{
    if((range.args_type == ITF_RANGE_FROM_TO || range.args_type == ITF_RANGE_FROM_TO) && range.args_len % 2 != 0) {
        //from-to and beyond can have multiple ranges, but each has to to have two values
        return;
    } else if((range.args_type == ITF_RANGE_FROM_TO || range.args_type == ITF_RANGE_BEYOND) && this->identity == ITF_INPUT_STRING) {
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

template<typename input_type>
bool itf_query_element<input_type>::range_from_to()
{
    for(int elm = 0; elm < this->local_range->args_len; elm += 2) {
        const int our_val = (int)this->local_val;
        const int our_from = (int)this->local_range->args[elm];
        const int our_to = (int)this->local_range->args[elm + 1];

        if(our_val >= our_from && our_val <= our_to) return true;
    }

    return false;
}

template<typename input_type>
bool itf_query_element<input_type>::range_beyond()
{
    for(int elm = 0; elm < this->local_range->args_len; elm += 2) {
        const int our_val = (int)this->local_val;
        const int our_from = (int)this->local_range->args[elm];
        const int our_to = (int)this->local_range->args[elm + 1];

        if(our_val >= our_from && our_val <= our_to) return false;
    }

    return true;
}

template<typename input_type>
bool itf_query_element<input_type>::range_is_in()
{
    const input_type local_compared = this->local_val;
    for(int elm = 0; elm < this->local_range->args_len; elm++) {
        if(local_compared == this->local_range->args[elm]) return true;
    }

    return false;
}

template<typename input_type>
bool itf_query_element<input_type>::range_not_in()
{
    const input_type local_compared = this->local_val;
    for(int elm = 0; elm < this->local_range->args_len; elm++) {
        if(local_compared == this->local_range->args[elm]) return false;
    }

    return true;
}