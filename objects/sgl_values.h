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

template <typename signal_type>
void sgl_type_setter(sgl_signal& to_set);

struct sgl_setter
{
    sgl_setter() : set_ptr(nullptr) {};
    void(*set_ptr)(sgl_signal& to_set);
};

class sgl_manager
{
public:
    sgl_manager(int& len, int*& depths, sgl_setter**& values) {
        if(len <= 0) {
            this->sectors_num = -1;
            this->sector_depths = nullptr;
            return;
        } else if(depths == nullptr) {
            this->sectors_num = -1;
            this->sector_depths = nullptr;
            return;
        } else if(values == nullptr) {
            this->sectors_num = -1;
            this->sector_depths = nullptr;
            return;
        }

        for(int check = 0; check < len; check++) {
            if(depths[check] <= 0) {
                this->sectors_num = -1;
                this->sector_depths = nullptr;
                return;
            }

            for(int further = 0; further < depths[check]; further++) {
                if(values[check][further].set_ptr == nullptr) {
                    this->sectors_num = -1;
                    this->sector_depths = nullptr;
                    return;
                }
            }
        }

        this->sectors_num = len;
        this->sector_depths = new int[this->sectors_num];

        for(int re_as = 0; re_as < len; re_as++) {
            this->sector_depths[re_as] = depths[re_as];
        }

        this->sectors_container = new sgl_signal*[this->sectors_num];

        for(int regions = 0; regions < this->sectors_num; regions++) {
            this->sectors_container[regions] = new sgl_signal[this->sector_depths[regions]];

            for(int further = 0; further < this->sector_depths[regions]; further++) {
                values[regions][further].set_ptr(this->sectors_container[regions][further]);
            }
        }
    };

    ~sgl_manager() {
        if(this->sector_depths != nullptr) {
            delete[] this->sector_depths;
        }

        if(this->sectors_container != nullptr) {
            for(int regions = 0; regions < this->sectors_num; regions++) {
                if(this->sectors_container[regions] != nullptr) {
                    delete[] this->sectors_container[regions];
                }
            }

            delete[] this->sectors_container;
        }
    };

private:
    int sectors_num;
    int* sector_depths;

    sgl_signal** sectors_container;
};

#endif