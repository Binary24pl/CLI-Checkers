template <typename sygnal_type>
void sgl_func_ptr_passer(sgl_signal*& to_config)
{
    if(to_config != nullptr) {
        //we need empty pointer for this function to do its thing
        return;
    }

    to_config = new sgl_signal(sgl_to_set<sygnal_type>, sgl_to_ret<sygnal_type>, sgl_to_ret<sygnal_type>);
}

template<typename sygnal_type>
void sgl_to_set(void*& val, const std::type_info& given_type)
{
    if(typeid(sygnal_type) != given_type) {
        //missmatch
        return;
    }
}