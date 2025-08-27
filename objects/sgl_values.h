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

        if(whatami == SGL_AUTH_GOD) {
            this->regions = new sgl_signal*[SGL_AUTH_COUNT];
            this->depths = new int[SGL_AUTH_COUNT];

            for(int make_null = 0; make_null < SGL_AUTH_COUNT; make_null++) {
                this->regions[make_null] = nullptr;
                this->depths[make_null] = -1; //as in emtpy data type
            }
        }
    }

    ~sgl_manager() {
        //only god-like manager can do clean up, and so best advised to keep god in pointer for better memory timing control
        if(this->identity == SGL_AUTH_GOD) {
            for(int i = 0; i < SGL_AUTH_COUNT; i++) {
                if(this->regions[i] != nullptr) delete[] this->regions[i];
            }

            delete[] this->regions;
            delete[] depths;
        }
    }

    void declare_region(const int& amount);
    void make_regions_depths();

private:
    static sgl_signal** regions;
    static int* depths;

    sgl_regional_auth identity;
};

sgl_signal** sgl_manager::regions = nullptr;
int* sgl_manager::depths = nullptr;


#endif