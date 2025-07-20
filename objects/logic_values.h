#ifndef LOGIC
#define LOGIC

enum logic_whatami_node {
    ITF_NODE_NONE
};

struct logic_passage_node {
    bool* scores;
    int* indexies;
    int count;
};

class logic_node {
public:
    logic_node(const logic_whatami_node& identity) {
        this->whatami = identity;
        this->prev_count = 0;
    };

    ~logic_node() {
        if(this->prev_count > 0) {
            delete[] this->prev_scores;
            delete[] this->prev_idx;
        }
    };

    logic_whatami_node whatami;
protected:
    bool* prev_scores;
    int* prev_idx;
    int prev_count;

    bool output;
};

#endif