template<typename input_type>
void itf_query_element<input_type>::assign_val(void*& val)
{
    input_type* caster = (input_type*) val;
    const input_type casted = *caster;

    this->ntv_assign_val(casted);
}

template<typename input_type>
void itf_query_element<input_type>::set_range(void*& set_range)
{}

template<typename input_type>
bool itf_query_element<input_type>::validate()
{}

template<typename input_type>
void itf_query_element<input_type>::ntv_assign_val(const input_type& val)
{
    this->local_val = val;

    std::cout << this->local_val << std::endl;
}