#ifndef SGL
#define SGL

class sgl_signal {
public:
    sgl_signal() {
        this->container = nullptr;

        this->cleaner = nullptr;
    };

    ~sgl_signal() {
        if(container != nullptr) {
            this->cleaner(container);
        }
    };

    bool self_validate();
private:
    void* container;

    void (*cleaner)(void*& to_clean);
};

template<typename signal_type>
void sgl_general_clear(void*& data);

template<typename signal_type>
void sgl_rephrase_signal_funcs(sgl_signal* our_signal);

#endif