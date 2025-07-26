void sgl_create_reco_list(std::vector<std::type_info>& our_data) {
    for(int idx = 0; idx < SGL_UT_END; idx++) {
        switch(idx) {
            case SGL_UT_INT: {
                our_data.push_back(typeid(int));
                break;
            }

            default: {
                our_data.push_back(typeid(sgl_type_error));
                break;
            }
        }
    }
}