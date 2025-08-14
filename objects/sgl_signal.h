template<typename signal_type>
void sgl_signal::set_message_type()
{
    if(this->container.msg_type != nullptr && this->container.message != nullptr) {
        if(this->container.cleaner == nullptr) {
            return;
        }

        this->container.cleaner(this->container);
    }

    signal_type* empty_val = new signal_type(sgl_invalid_value<signal_type>::get());

    container.message = empty_val;
    container.msg_type = &typeid(signal_type);
    container.cleaner = sgl_cleaner<signal_type>;
}