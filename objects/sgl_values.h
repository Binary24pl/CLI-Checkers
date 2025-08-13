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
private:
    void* container;

    void (*cleaner)(void*& to_clean);

    bool self_validate();
};

template<typename signal_type>
void sgl_rephrase_signal_funcs(sgl_signal* our_signal);

#endif