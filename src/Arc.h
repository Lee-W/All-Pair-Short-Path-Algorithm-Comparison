#ifndef ARC_H
#define ARC_H

#include <climits>

#define INF INT_MAX / 2

struct Arc {
    Arc()
    {
        from = -1;
        to = -1;
        arcLength = INT_MAX / 2;
    }

    Arc(int f, int t, double l)
    {
        from = f;
        to = t;
        arcLength = l;
    }

    int from;
    int to;
    double arcLength;
};

#endif
