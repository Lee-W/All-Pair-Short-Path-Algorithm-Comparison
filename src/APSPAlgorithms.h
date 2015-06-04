#ifndef APSP_ALGORITHMS_H
#define APSP_ALGORITHMS_H

#include <iostream>
#include <ctime>
#include <vector>
#include <algorithm>
#include "Arc.h"
using namespace std;

class APSPAlgorithms {
public:
    clock_t countTime(void (*func)());
    void initial(int n, vector<Arc> arcs);
    void AlgebraicalFloydWarshall();
    void GraphicalFloydWarshall();

    vector<vector<int> > getDis();
    vector<vector<int> > getPre();
    clock_t getProcessTime();
    int getRelaxNum();

private:
    vector<vector<int> > dis;
    vector<vector<int> > pre;
    int nodeNum;
    vector<Arc> arcs;

    clock_t processTime;
    int relaxNum;

    static bool arcCmp(Arc a1, Arc a2);
};

#endif
