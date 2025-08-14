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

template<typename signal_type>
void sgl_signal::get_message(signal_type& reciever)
{
    if(this->container.msg_type == nullptr) {
        return;
    } else if(this->container.msg_type != &typeid(signal_type)) {
        return;
    } else if(this->container.message == nullptr) {
        return;
    }

    signal_type* reader = (signal_type*)this->container.message;
    reciever = *reader;
}

template<typename signal_type>
void sgl_signal::set_message(signal_type& setter)
{
    if(this->container.msg_type == nullptr) {
        return;
    } else if(this->container.msg_type != &typeid(signal_type)) {
        return;
    } else if(this->container.cleaner == nullptr) {
        return;
    }

    signal_type* remover = (signal_type*)this->container.message;
    this->container.message = nullptr;

    delete remover;

    signal_type* caster = new signal_type;
    *caster = setter;

    this->container.message = (void*)caster;
}