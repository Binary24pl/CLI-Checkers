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

template<typename input_type>
void itf_question::give_element_range(const itf_input_range<input_type>& range, const int& position)
{
    itf_input_whatami our_identity;

    if(this->verify_type<itf_input_range<int>>(range)) {
        our_identity = ITF_INPUT_INT;
    } else if(this->verify_type<itf_input_range<char>>(range)) {
        our_identity = ITF_INPUT_CHAR;
    } else if(this->verify_type<itf_input_range<std::string>>(range)) {
        our_identity = ITF_INPUT_STRING;
    } else {
        our_identity = ITF_INPUT_ERROR;
    }

    //time to safefail
    if(our_identity == ITF_INPUT_ERROR) {
        return;
    }

    if(position >= 0 && position < this->question_length) {
        if(this->question_form[0]->identity != our_identity) {
            return;
        }
    } else {
        return;
    }

    if(range.args == nullptr) {
        return;
    }

    common_passer(range, this->question_form[0], &ITF::itf_query_master::set_range);
}

template <typename compared, typename input_type> 
bool itf_question::verify_type(const input_type& to_check)
{
    compared test_var;
    
    if(typeid(test_var) == typeid(to_check)) {
        return true;
    }

    return false;
}

void itf_question::define_return_values(const int& size, int*& positions)
{
    if(this->question_form == nullptr) {
        return;
    }

    if(size < 0 || size > this->question_length) {
        return;
    }

    if(this->main_vals_pos != nullptr) {
        int* temp = this->main_vals_pos;
        this->main_vals_pos = nullptr;

        delete[] temp;
    }

    if(this->main_vals_identities != nullptr) {
        itf_input_whatami* temp = this->main_vals_identities;
        this->main_vals_identities = nullptr;

        delete[] temp;
    }

    this->main_vals_pos = new int[size];
    this->main_vals_identities = new itf_input_whatami[size];

    for(int idx = 0; idx < size; idx++) {
        this->main_vals_pos[idx] = positions[idx];
        this->main_vals_identities[idx] = this->question_form[positions[idx]]->identity;
    }

    this->main_vals_len = size;
}