#ifndef SGL
#define SGL

class sgl_signal {
public:
    sgl_signal(void(*data_setter)(void*&, const std::type_info&), void(*data_returner)(void*&), void(*data_cleaner)(void*&)) {
        if(data_setter == nullptr || data_returner == nullptr || data_cleaner == nullptr) {
            this->set_data = nullptr;
            this->return_data = nullptr;
            this->clean_data = nullptr;

            //return early for an error state
            return;
        }

        this->set_data = data_setter;
        this->return_data = data_returner;
        this->clean_data = data_cleaner;
    };

    void(*set_data)(void*&, const std::type_info&);
    void(*return_data)(void*&);
    void(*clean_data)(void*&);
};

template<typename sygnal_type>
void sgl_to_set(void*& val, const std::type_info& given_type);

template<typename sygnal_type>
void sgl_to_ret(void*& val);

template<typename sygnal_type>
void sgl_to_clr(void*& val);

template <typename sygnal_type>
void sgl_func_ptr_passer(sgl_signal*& to_config);

#endif