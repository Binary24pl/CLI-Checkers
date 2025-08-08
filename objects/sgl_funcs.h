template <typename sygnal_type>
void sgl_func_ptr_passer(sgl_signal*& to_config)
{
    if(to_config != nullptr) {
        //we need empty pointer for this function to do its thing
        return;
    }

    to_config = new sgl_signal(sgl_to_set<sygnal_type>, sgl_to_ret<sygnal_type>, sgl_to_ret<sygnal_type>);
}