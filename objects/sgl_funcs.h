template<typename cast> void sgl_data_setter(sgl_data& holder)
{
    if(holder.value != nullptr) {
        holder.cleanup_func(holder);
    }

    holder.value = nullptr;

    holder.cleanup_func = &sgl_data_cleaner<cast>;
    holder.caster_func = &sgl_data_caster<cast>;
    holder.recaster_func = &sgl_data_recaster<cast>;
    holder.identifier = &typeid(cast);
}

template<typename cast> void sgl_data_cleaner(sgl_data& holder)
{
    if(holder.value == nullptr) {
        return;
    }

    cast* to_clean = (cast*)holder.value;
    delete to_clean;
}

template<typename cast> void sgl_data_caster(void*& val, sgl_data& holder)
{
    cast* val_old = (cast*)val;
    cast* val_new = new cast;

    *val_new = *val_old;
    holder.cleanup_func(holder);
    holder.value = (void*)val_new;
}

template<typename cast> void sgl_data_recaster(void*& val, sgl_data& holder)
{
    cast* val_old = (cast*)holder.value;
    cast* val_new = new cast;

    *val_new = *val_old;

    val = (void*)val_new;
}

template<typename pass> void sgl_data_passer(const pass& val, sgl_data& holder, const bool& is_new)
{
    if(is_new) {
        holder.value = nullptr;
        sgl_data_setter<pass>(holder);
    } else {
        if(&typeid(pass) != holder.identifier) {
            return;
        }
    }

    pass* to_cast = new pass;
    *to_cast = val;

    void* to_pass = (void*)to_cast;

    holder.caster_func(to_pass, holder);

    delete to_cast;
}

template<typename pass> void sgl_data_repasser(pass& val, sgl_data& holder) {
    if(holder.value == nullptr || &typeid(pass) != holder.identifier) {
        return;
    }

    void* to_cast;
    holder.recaster_func(to_cast, holder);

    pass* to_pass = (pass*)to_cast;

    val = *to_pass;

    delete to_pass;
}