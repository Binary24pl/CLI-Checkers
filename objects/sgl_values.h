#ifndef SGL
#define SGL

struct sgl_data {
    void* value;
    void (*caster_func)(void*&, sgl_data&);
    void (*recaster_func)(void*&, sgl_data&);
    void (*cleanup_func)(sgl_data&);
    const std::type_info* identifier;
};
//for memory heap safety, always set value as nullptr at the begining of its life

template<typename cast> void sgl_data_caster(void*& val, sgl_data& holder);
template<typename cast> void sgl_data_recaster(void*& val, sgl_data& holder);

template<typename cast> void sgl_data_setter(sgl_data& holder);
template<typename cast> void sgl_data_cleaner(sgl_data& holder);

template<typename pass> void sgl_data_passer(const pass& val, sgl_data& holder);
template<typename pass> void sgl_data_repasser(pass& val, sgl_data& holder);

#endif