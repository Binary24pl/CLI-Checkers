#ifndef SGL
#define SGL

template<typename T>
struct sgl_invalid_value {
    static T get() { return T(); }
};

template<>
struct sgl_invalid_value<std::string> {
    static std::string get() { return "INVALID"; }
};

template<>
struct sgl_invalid_value<int> {
    static int get() { return -1; }
};

template<>
struct sgl_invalid_value<char> {
    static char get() { return '*'; }
};

struct sgl_medium
{
    void* message;
    const std::type_info* msg_type;

    void(*cleaner)(sgl_medium& to_clean);
};

template<typename signal_type>
void sgl_cleaner(sgl_medium& to_clean);

class sgl_signal
{
public:
    sgl_signal() {
        //nulling some thingies
        this->container.message = nullptr;
        this->container.msg_type = nullptr;

        this->container.cleaner = nullptr;
    }

    ~sgl_signal() {
        if(this->container.msg_type != nullptr && this->container.message != nullptr) {
            this->container.cleaner(this->container);
        }
    }

    template<typename signal_type>
    void set_message_type();

    template<typename signal_type>
    void get_message(signal_type& reciever);

    template<typename signal_type>
    void set_message(signal_type& setter);

private:
    sgl_medium container;
};

enum sgl_regional_auth {
    SGL_AUTH_GOD,
    SGL_AUTH_COUNT
};

class sgl_manager
{
public:
    sgl_manager(const sgl_regional_auth& whatami) {
        this->identity = whatami;

        if(whatami == SGL_AUTH_COUNT) {
            return;
        }
    }

    ~sgl_manager() {
        //only god-like manager can do clean up, and so best advised to keep god in pointer for better memory timing control
        if(this->identity = SGL_AUTH_GOD) {
            for(int i = 0; i < SGL_AUTH_COUNT; i++) {
                delete[] this->regions[i];
            }

            delete[] this->regions;
        }
    }

private:
    static sgl_signal** regions;

    sgl_regional_auth identity;
};

sgl_signal** sgl_manager::regions = nullptr;


#endif