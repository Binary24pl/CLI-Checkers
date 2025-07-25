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
        if(this->question_form[position]->identity != our_identity) {
            return;
        }
    } else {
        return;
    }

    if(range.args == nullptr) {
        return;
    }

    common_passer(range, this->question_form[position], &ITF::itf_query_master::set_range);
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

void itf_question::ask_question()
{
    while (true)
    {
        this->hint_syntax();
        std::vector<std::string> raw_version;
        std::string raw_element = "";

        while (std::cin >> raw_element)
        {
            raw_version.push_back(raw_element);
            if(std::cin.peek() == '\n') {
                break;
            }
        }

        if(this->validate_question(raw_version)) {
            break;
        }
    }
    
}

bool itf_question::validate_question(const std::vector<std::string>& raw_question)
{
    if(raw_question.size() != this->question_length) {
        return false;
    }

    for(int idx = 0; idx < raw_question.size(); idx++) {
        std::string our_element = raw_question[idx];
        itf_input_whatami our_identity = this->question_form[idx]->identity;

        switch(our_identity) {
        case ITF_INPUT_STRING: {
            common_passer(our_element, this->question_form[idx], &ITF::itf_query_master::assign_val);
            break;
        }
        case ITF_INPUT_CHAR: {
            if(our_element.length() != 1) {
                return false;
            }

            char our_trans_elm = our_element[0];

            common_passer(our_trans_elm, this->question_form[idx], &ITF::itf_query_master::assign_val);
            break;
        }
        case ITF_INPUT_INT: {
            const int zero_char = (int)'0';
            for(int check_num = 0; check_num < our_element.length(); check_num++) {
                const int our_digit = (int)our_element[check_num];

                if(our_digit < zero_char || our_digit > zero_char + 9) {
                    return false;
                }
            }

            int our_num = common_translate_value<std::string, int>(our_element);
            common_passer(our_num, this->question_form[idx], &ITF::itf_query_master::assign_val);
            break;
        }
        default:
            break;
        }

        if(this->question_form[idx]->validate() == false) return false;
    }

    return true;
}

void itf_question::hint_syntax()
{
    std::string to_show = "Your entry formula: \n";
    itf_text_pallete value, option;
    
    value.bg_color = ITF_C_BLACK;
    value.bg_inten = ITF_LOW_INTEN;
    value.fg_color = ITF_C_CYAN;
    value.fg_inten = ITF_HIGH_INTEN;

    option.bg_color = ITF_C_BLACK;
    option.bg_inten = ITF_HIGH_INTEN;
    option.fg_color = ITF_C_GREEN;
    option.fg_inten = ITF_LOW_INTEN;

    const int len = this->question_length;
    for(int elms = 0; elms < len; elms++) {
        if(this->question_form[elms] != nullptr) {
            const itf_input_whatami check_identity = this->question_form[elms]->identity;

            switch(check_identity) {
                case ITF_INPUT_CHAR: {
                    to_show += itf_give_color("<character>", value);

                    if(this->question_form[elms]->is_range_set()) {
                        std::string digested = this->hint_range_digest<char>(elms);

                        digested = itf_give_color(digested, option);

                        to_show += ":: ";
                        to_show += digested;
                    }
                    break;
                }

                case ITF_INPUT_INT: {
                    to_show += itf_give_color("<integer>", value);

                    if(this->question_form[elms]->is_range_set()) {
                        std::string digested = this->hint_range_digest<int>(elms);

                        digested = itf_give_color(digested, option);

                        to_show += ":: ";
                        to_show += digested;
                    }
                    break;
                }

                case ITF_INPUT_STRING: {
                    to_show += itf_give_color("<text>", value);

                    if(this->question_form[elms]->is_range_set()) {
                        std::string digested = this->hint_range_digest<std::string>(elms);

                        digested = itf_give_color(digested, option);

                        to_show += ":: ";
                        to_show += digested;
                    }
                    break;
                }

                default:
                    break;
            }

            if(elms < len - 1) to_show += ", ";
        }
    }

    std::cout << to_show << std::endl;
}

template<typename input_type> 
std::string itf_question::hint_range_digest(const int& pos)
{

    std::string to_return = "";
    void* taker;

    this->question_form[pos]->return_range(taker);
    
    itf_input_range<input_type>* reader = (itf_input_range<input_type>*)taker;

    const itf_inrange_type our_type = reader->args_type;
    bool slash_or_dash; // true = slash, false = dash
    int incrementation;

    switch(our_type)
    {
        case ITF_RANGE_IS_IN: {
            to_return += "Must be one of these: (";
            slash_or_dash = true;
            incrementation = 1;
            break;
        }

        case ITF_RANGE_IS_NOT_IN: {
            to_return += "Can't be one of these: (";
            slash_or_dash = true;
            incrementation = 1;
            break;
        }

        case ITF_RANGE_FROM_TO: {
            to_return += "Must fit within this set of ranges: (";
            slash_or_dash = false;
            incrementation = 2;
            break;
        }

        case ITF_RANGE_BEYOND: {
            to_return += "Can't fit within this set of ranges: (";
            slash_or_dash = false;
            incrementation = 2;
            break;
        }

        default:
            break;
    }

    const int len = reader->args_len;
    for(int idx = 0; idx < len; idx += incrementation) {
        if(slash_or_dash) {
            input_type raw_form = reader->args[idx];
            
            std::string digested_form = common_translate_value<input_type, std::string>(raw_form);
            to_return += digested_form;
        } else {
            input_type raw_left, raw_right;

            raw_left = reader->args[idx];
            raw_right = reader->args[idx + 1];

            std::string digested_form = "";

            digested_form += common_translate_value<input_type, std::string>(raw_left);
            digested_form += "-";
            digested_form += common_translate_value<input_type, std::string>(raw_right);

            to_return += digested_form;
        }

        if(idx < len - incrementation) to_return += "/";
    }

    to_return += ")";

    delete[] reader->args;
    delete reader;

    return to_return;
}

//todo: hint system