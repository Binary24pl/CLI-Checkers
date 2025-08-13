template<typename signal_type>
void sgl_rephrase_signal_funcs(sgl_signal* our_signal)
{
    if(our_signal == nullptr) {
        std::cout << "data is unset" << std::endl;
    } else {
        std::cout << "data is set" << std::endl;
    }
}