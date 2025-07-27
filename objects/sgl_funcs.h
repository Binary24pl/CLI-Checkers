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

template<typename pass> void sgl_data_passer(const pass& val, sgl_data& holder)
{
    if(&typeid(pass) != holder.identifier) {
        return;
    }

    pass* val_caster = new pass;
    *val_caster = val;

    void* val_passer = (void*)val_caster;
    holder.caster_func(val_passer, holder);

    delete val_caster;
}

template<typename pass> void sgl_data_repasser(pass& val, sgl_data& holder)
{
    if(&typeid(pass) != holder.identifier) {
        return;
    }

    void* val_old;
    holder.recaster_func(val_old, holder);

    pass* val_new = (pass*)val_old;

    val = *val_new;
    delete val_new;
}