void itf_question::cleanup_question()
{
    if(this->question_form == nullptr) {
        //we dont want do double free do we;
        return;
    }

    const int len = this->question_length;
    for(int elm = 0; elm < len; elm++) {
        if(question_form[elm] != nullptr) {
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
    }

    itf_query_master** temp_holder;
    temp_holder = this->question_form;

    this->question_form = nullptr;
    this->question_length = 0;
    delete[] temp_holder;
}

void itf_question::start_new_question(const int& size)
{
    this->cleanup_question();
    this->question_form = new itf_query_master*[size];

    for(int t_nl = 0; t_nl < size; t_nl++) {
        this->question_form[t_nl] = nullptr;
    }

    this->question_length = size;
}

void itf_question::build_into_question(const itf_input_whatami& what_kind, const int& what_posiiton)
{
    if(what_posiiton < 0 || what_posiiton >= this->question_length) return;

    if(this->question_form[what_posiiton] != nullptr) {
        switch(this->question_form[what_posiiton]->identity) {
        case ITF_INPUT_INT:
            delete (itf_query_element<int>*)this->question_form[what_posiiton];
            break;
        case ITF_INPUT_CHAR:
            delete (itf_query_element<char>*)this->question_form[what_posiiton];
            break;
        case ITF_INPUT_STRING:
            delete (itf_query_element<std::string>*)this->question_form[what_posiiton];
            break;
        default:
            break;
        }
    }

    switch(what_kind) {
    case ITF_INPUT_INT:
        this->question_form[what_posiiton] = new itf_query_element<int>;
        break;
    case ITF_INPUT_CHAR:
        this->question_form[what_posiiton] = new itf_query_element<char>;
        break;
    case ITF_INPUT_STRING:
        this->question_form[what_posiiton] = new itf_query_element<std::string>;
        break;
    default:
        break;
    }
}