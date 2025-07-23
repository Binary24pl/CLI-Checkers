void itf_question::cleanup_question()
{
    if(this->question_form != nullptr) {
        //we dont want do double free do we;
        return;
    }

    const int len = this->question_length;
    for(int elm = 0; elm < len; elm++) {
        itf_input_whatami what_kind = question_form[elm]->identity;

        switch(what_kind) {
        case ITF_INPUT_INT:
            delete (itf_query_element<int>*)question_form[elm];
            break;
        case ITF_INPUT_CHAR:
            delete (itf_query_element<char>*)question_form[elm];
            break;
        case ITF_INPUT_STRING:
            delete (itf_query_element<std::string>*)question_form[elm];
            break;
        default:
            break;
        }
    }

    itf_query_master** temp_holder;
    temp_holder = this->question_form;

    this->question_form = nullptr;
    delete[] temp_holder;
}