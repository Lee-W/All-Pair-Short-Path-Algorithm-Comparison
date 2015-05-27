#ifndef NODE_H
#define NODE_H

#include <climits>

struct Node {
    Node()
    {
        index = -1;
        dis = INT_MAX / 2;
    }

    Node(int i, int d)
    {
        index = i;
        dis = d;
    }

    bool operator==(Node n2) { return (index == n2.index) && (dis == n2.dis); }

    bool operator>(Node n2) { return (dis > n2.dis); }

    bool operator<(Node n2) { return (dis < n2.dis); }

    int index;
    int dis;
};

#endif
