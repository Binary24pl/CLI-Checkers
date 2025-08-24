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

class sgl_manager
{
public:
    sgl_manager() {}

    ~sgl_manager() {}

    static void read();
    static void push(int val);
    static std::vector<int> test;
};

#endif