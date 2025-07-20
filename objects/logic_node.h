void logic_node::connected_from(const int& id, const int& priority)
{
    if(this->prev_to_occupy == this->prev_count) {
        this->prev_to_occupy *= 2;

        int* temp_idx = new int[this->prev_to_occupy];
        int* temp_priority = new int[this->prev_to_occupy];

        for(int lcl_t_tmp = 0; lcl_t_tmp < this->prev_count; lcl_t_tmp++) {
            temp_idx[lcl_t_tmp] = this->prev_idx[lcl_t_tmp];
            temp_priority[lcl_t_tmp] = this->prev_priority[lcl_t_tmp];
        }

        int* to_dlt_idx;
        int* to_dlt_priority;

        to_dlt_idx = this->prev_idx;
        to_dlt_priority = this->prev_priority;

        this->prev_idx = temp_idx;
        this->prev_priority = temp_priority;

        delete[] to_dlt_idx;
        delete[] to_dlt_priority;
    }

    this->prev_idx[this->prev_count] = id;
    this->prev_priority[this->prev_count] = priority;

    this->prev_count += 1;
}