#ifndef SSSP_ALGORITHMS_H
#define SSSP_ALGORITHMS_H

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include "Arc.h"
#include "Node.h"
#include "MinHeap.h"
using namespace std;

class SSSPAlgorithms {
public:
    void initial(int n, vector<Arc> arcs);

    void DijkstraWithBinaryHeap(int source);
    void Dial(int source);

    // Bellman Ford with Queue
    void SPFA(int source);

    // Bellman Ford with Dequeue
    void PAPE(int source);

    vector<int> getDis();
    vector<int> getPre();

private:
    vector<vector<Arc> > network;
    vector<int> dis;
    vector<int> pre;
    int nodeNum;

    void vectorDelete(vector<int>& v, int value);
    int countMaxBucketSize();
};

#endif
