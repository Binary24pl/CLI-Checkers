void gam_mainloop::init()
{
    if(this->game_height == -1 || this->game_width == -1) return;

    this->logic = new GAM::gam_board(this->game_height, this->game_width);
    this->display = new ITF::itf_board(this->game_height, this->game_width);

    this->logic->init();
    this->display->init();

    this->ask_confirm = new ITF::itf_question();
    this->ask_coords = new ITF::itf_question();

    this->set_questions();
}

void gam_mainloop::set_questions()
{
    this->ask_confirm->start_new_question(1);
    this->ask_coords->start_new_question(2);

    this->ask_confirm->build_into_question(ITF_INPUT_STRING, 0);
    itf_input_range<std::string> confirm_range;
    confirm_range.args_len = 2;
    confirm_range.args_type = ITF_RANGE_IS_IN;
    confirm_range.args = new std::string[2];

    confirm_range.args[0] = "confirm";
    confirm_range.args[1] = "cancel";

    this->ask_confirm->give_element_range<std::string>(confirm_range, 0);

    this->ask_coords->build_into_question(ITF_INPUT_CHAR, 0);
    this->ask_coords->build_into_question(ITF_INPUT_INT, 1);

    itf_input_range<char> on_hght_rng;
    on_hght_rng.args_len = 2;
    on_hght_rng.args_type = ITF_RANGE_FROM_TO;
    on_hght_rng.args = new char[2];

    on_hght_rng.args[0] = 'A';
    on_hght_rng.args[1] = (char)((int)'A' + (this->game_height - 1));
    this->ask_coords->give_element_range<char>(on_hght_rng, 0);


    itf_input_range<int> on_wdth_rng;
    on_wdth_rng.args_len = 2;
    on_wdth_rng.args_type = ITF_RANGE_FROM_TO;
    on_wdth_rng.args = new int[2];

    on_wdth_rng.args[0] = 1;
    on_wdth_rng.args[1] = this->game_width;

    this->ask_coords->give_element_range<int>(on_wdth_rng, 1);

    delete[] confirm_range.args;
    delete[] on_hght_rng.args;
    delete[] on_wdth_rng.args;
}

void gam_mainloop::run_loop(bool& controler)
{
    system("clear");
    controler = false;
}