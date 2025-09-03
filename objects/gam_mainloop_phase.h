void gam_mainloop::phase_start()
{
    this->display->read_vals(this->logic->communicate_draw(this->current_team, GAM_DRW_SLCTB));
    this->display->show_visual_state();

    common_position to_select;
    while (true)
    {
        std::vector<std::string> raw_select = this->ask_coords->ask_question();
        to_select = this->status_coords(raw_select);

        gam_select_results results = this->logic->scenario_select(this->current_team, to_select);

        if(results == GAM_SLT_VALID) {
            break;
        }
    }
    
    this->cursor.on_height = to_select.on_height;
    this->cursor.on_width = to_select.on_width;

    this->current_phase = GAM_PHS_SELECTED;
}

void gam_mainloop::phase_selected()
{
    this->display->read_vals(this->logic->communicate_draw(this->current_team, GAM_DRW_SLCTD, this->cursor));
    this->display->show_visual_state();

    common_position to_select;
    while(true)
    {
        std::vector<std::string> raw_select = this->ask_coords->ask_question();
        to_select = this->status_coords(raw_select);

        gam_select_results results = this->logic->scenario_pre_move(this->current_team, this->cursor, to_select);

        if(results != GAM_SLT_INVALID) {
            if(results == GAM_SLT_UNSELECT) {
                this->current_phase = GAM_PHS_START;
            } else {
                this->current_phase = GAM_PHS_PRE_MOVE;
                
                this->selector.on_height = to_select.on_height;
                this->selector.on_width = to_select.on_width;
            }

            break;
        }
    }
}

void gam_mainloop::phase_pre_move()
{
    this->display->read_vals(this->logic->communicate_draw(this->current_team, GAM_DRW_TCNFRM, this->cursor, this->selector, this->status_enemy()));
    this->display->show_visual_state();

    bool to_confirm = this->status_confirm(this->ask_confirm->ask_question());
    
    if(to_confirm) {
        this->current_phase = GAM_PHS_MOVED;
    } else {
        this->current_phase = GAM_PHS_SELECTED;
    }
}

void gam_mainloop::phase_moved()
{
    gam_move_results results = this->logic->scenario_post_move(this->current_team ,this->cursor, this->selector);

    if(results == GAM_MOV_FINISHED) {
        this->current_phase = GAM_PHS_FINISHED;
    } else if(results == GAM_MOV_UNFINISHED) {
        this->current_phase = GAM_PSH_PRE_CHAIN;

        this->cursor.on_height = this->selector.on_height;
        this->cursor.on_width = this->selector.on_width;
    }
}

void gam_mainloop::phase_pre_chain()
{
    this->display->read_vals(this->logic->communicate_draw(this->current_team, GAM_DRW_CHAIN, this->cursor));
    this->display->show_visual_state();

    while (true)
    {
        common_position to_move = this->status_coords(this->ask_coords->ask_question());

        gam_select_results results = this->logic->scenario_pre_restrike(this->current_team, this->cursor, to_move);

        if(results != GAM_SLT_INVALID) {
            this->selector.on_height = to_move.on_height;
            this->selector.on_width = to_move.on_width;

            this->current_phase = GAM_PHS_AT_RECHAIN;
            break;
        }
    }
    
}

void gam_mainloop::phase_at_re_chain()
{
    this->display->read_vals(this->logic->communicate_draw(this->current_team, GAM_DRW_TCNFRM, this->cursor, this->selector, this->status_enemy()));
    this->display->show_visual_state();

    bool question = this->status_confirm(this->ask_confirm->ask_question());
    if(question) {
        gam_move_results results = this->logic->scenario_restrike(this->current_team, this->cursor, this->selector);

        if(results == GAM_MOV_FINISHED) {
            this->current_phase = GAM_PHS_FINISHED;
        } else {
            this->current_phase = GAM_PSH_PRE_CHAIN;

            this->cursor.on_height = this->selector.on_height;
            this->cursor.on_width = this->selector.on_width;
        }
    } else {
        this->current_phase = GAM_PSH_PRE_CHAIN;
    }
}

void gam_mainloop::phase_finished()
{
    if(this->current_team) {
        this->current_team = GAM_DARK;
    } else {
        this->current_team = GAM_LIGHT;
    }

    this->current_phase = GAM_PHS_START;
}