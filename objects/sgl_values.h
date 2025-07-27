#ifndef SGL
#define SGL

enum sgl_type_idx {
    SGL_TYPE_INT,
    SGL_TYPE_CHAR,
    SGL_TYPE_TOTAL
};

struct sgl_wrong_data_type {};

//remember always &typeid(typename) for our la values
void sgl_make_reco_list(std::vector<const std::type_info*>& our_list);
void sgl_debbug_read(std::vector<const std::type_info*>& our_list);

#endif