template<typename signal_type>
void sgl_signal::set_message_type()
{
    if(this->container.msg_type != nullptr && this->container.message != nullptr) {
        if(this->container.cleaner == nullptr) {
            return;
        }

        this->container.cleaner(this->container);
    }

    signal_type* empty_val = new signal_type;
}