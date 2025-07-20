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

        this->prev_to_occupy = 2;
        this->prev_idx = new int[this->prev_to_occupy];
        this->prev_priority = new int[this->prev_to_occupy];
    };

    ~logic_node() {
        delete[] prev_idx;
        delete[] prev_priority;
    };

    logic_whatami_node whatami;
    
    void connected_from(const int& id, const int& priority);
    bool output;
protected:
    int* prev_idx;
    int* prev_priority;
    int prev_count;
    int prev_to_occupy;
};

#endif