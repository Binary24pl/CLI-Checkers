#ifndef LOGIC
#define LOGIC

enum logic_whatami_node {
    LOGIC_NODE_NONE
};

//these nodes will be used by various logic thingies
class logic_node {
public:
    logic_node(const logic_whatami_node& identity) {
        this->whatami = identity;
        this->prev_count = 0;
    };

    ~logic_node() {
        std::cout << "From parent" << std::endl;

        if(this->prev_count > 0) {
            delete[] this->prev_scores;
            delete[] this->prev_idx;
        }
    };

    logic_whatami_node whatami;
    
    void connected_from(const int& id, const int& priority);
protected:
    bool* prev_scores;
    int* prev_idx;
    int* prev_priority;
    int prev_count;

    bool output;
};

#endif