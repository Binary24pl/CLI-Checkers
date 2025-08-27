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

template <typename input_type>
void sgl_set_type(sgl_signal*& to_edit)
{
    to_edit->set_message_type<input_type>();
}

template<typename signal_type>
void sgl_set_pattern(sgl_pattern& to_edit) 
{
    to_edit.typer = sgl_set_type<signal_type>;
    to_edit.our_type = sgl_get_data_type<signal_type>();
}