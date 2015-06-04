#include <iostream>
#include "Node.h"
using namespace std;

class NodeComparator {
public:
    bool operator() (const Node& n1, const Node& n2);
};
