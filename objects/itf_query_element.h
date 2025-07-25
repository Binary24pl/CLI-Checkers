// deemed: unifinished

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
     //de_alloc id: 5
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
void itf_query_element<input_type>::give_val(void*& caller) {
    itf_query_element<input_type>* other = (itf_query_element<input_type>*)caller;

    input_type* caster = new input_type;
    const input_type to_cast = this->local_val;
    *caster = to_cast;

    void* passer;
    passer = (void*)caster;

    other->assign_val(passer);

    delete caster;
}

template<typename input_type>
void itf_query_element<input_type>::give_range(void*& caller)
{
    if(this->local_range == nullptr) return;

    itf_query_element<input_type>* other = (itf_query_element<input_type>*)caller;
    itf_input_range<input_type>* caster = new itf_input_range<input_type>;

    caster->args_len = this->local_range->args_len;
    caster->args_type = this->local_range->args_type;
    caster->args = new input_type[caster->args_len];

    for(int idx = 0; idx < this->local_range->args_len; idx++) {
        caster->args[idx] = this->local_range->args[idx];
    }

    void* passer;
    passer = (void*)caster;

    other->set_range(passer);

    delete[] caster->args;
    delete caster;
}

template<typename input_type>
void itf_query_element<input_type>::return_val(void*& carrier)
{
    input_type* caster = new input_type;
    *caster = this->local_val;

    carrier = (void*)caster;
}

template<typename input_type>
void itf_query_element<input_type>::return_range(void*& carrier)
{
    itf_input_range<input_type>* caster = new itf_input_range<input_type>;
    
    const int len = this->local_range->args_len;
    caster->args_len = len;
    caster->args_type = this->local_range->args_type;

    caster->args = new input_type[len];

    for(int idx = 0; idx < len; idx++) {
        caster->args[idx] = this->local_range->args[idx];
    }

    carrier = (void*)caster;
}

template<typename input_type>
bool itf_query_element<input_type>::is_range_set()
{
    if(this->local_range != nullptr) return true;
    return false;
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
        const input_type our_val = this->local_val;
        const input_type our_from = this->local_range->args[elm];
        const input_type our_to = this->local_range->args[elm + 1];

        if(our_val >= our_from && our_val <= our_to) return true;
    }

    return false;
}

template<typename input_type>
bool itf_query_element<input_type>::range_beyond()
{
    for(int elm = 0; elm < this->local_range->args_len; elm += 2) {
        const input_type our_val = this->local_val;
        const input_type our_from = this->local_range->args[elm];
        const input_type our_to = this->local_range->args[elm + 1];

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