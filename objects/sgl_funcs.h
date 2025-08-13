template<typename signal_type>
void sgl_general_clear(void*& data)
{
    signal_type* caster = (signal_type*)data;
    delete caster;
}

template<typename signal_type>
void sgl_rephrase_signal_funcs(sgl_signal* our_signal)
{
    if(our_signal == nullptr) {
        return;
    }

    if(our_signal->self_validate()) {
        std::cout << "data is clear" << std::endl;
    } else {
        std::cout << "data is unclear" << std::endl;
    }
}