template<typename signal_type>
void sgl_cleaner(sgl_medium& to_clean)
{
    if(to_clean.message == nullptr || to_clean.msg_type == nullptr) {
        return;
    }

    void* taken_content = to_clean.message;
    signal_type* correct_cleaner = (signal_type*)taken_content;

    delete correct_cleaner;

    to_clean.message = nullptr;
    to_clean.msg_type = nullptr;

    to_clean.cleaner = nullptr;
}

template <typename signal_type>
void sgl_type_setter(sgl_signal& to_set)
{
    to_set.set_message_type<signal_type>();
}