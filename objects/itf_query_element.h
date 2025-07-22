template<typename input_type>
void itf_query_element<input_type>::test(void*& val)
{
    input_type* re_caster = (input_type*)val;

    std::cout << "Hello and to you mr. value: " << *re_caster << std::endl;
}