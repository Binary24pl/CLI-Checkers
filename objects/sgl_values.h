#ifndef SGL
#define SGL

enum sgl_used_type {
    SGL_UT_INT,
    SGL_UT_CHAR,
    SGL_UT_STRING,
    SGL_UT_END
};

struct sgl_type_error {};

struct sgl_data_holder {
    void* value;
    std::type_info real_type;
};

void sgl_create_reco_list(std::vector<std::type_info>& our_data);
class sgl_data_container {
public:
    sgl_data_container() {
        sgl_create_reco_list(valid_datas);
    };

    ~sgl_data_container() {};
private:
    std::vector<std::type_info> valid_datas;
};

#endif