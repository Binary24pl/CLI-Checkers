void sgl_make_reco_list(std::vector<const std::type_info*>& our_list)
{
    for(int type_i = 0; type_i < SGL_TYPE_TOTAL; type_i++) {
        switch(type_i) {
            case SGL_TYPE_INT: {
                our_list.push_back(&typeid(int));
                break;
            }

            case SGL_TYPE_CHAR: {
                our_list.push_back(&typeid(char));
                break;
            }

            default: {
                our_list.push_back(&typeid(sgl_wrong_data_type));
                break;
            }
        }
    }
}

void sgl_debbug_read(std::vector<const std::type_info*>& our_list)
{
    for(int type_i = 0; type_i < SGL_TYPE_TOTAL; type_i++) {
        std::cout << type_i << " : " << our_list[type_i]->name() << std::endl;
    }
}