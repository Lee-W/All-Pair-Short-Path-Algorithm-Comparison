#ifndef SSSP_ALGORITHMS_H
#define SSSP_ALGORITHMS_H

#include <iostream>
#include <vector>
#include <map>
#include <deque>
#include <queue>
#include <algorithm>
#include "Arc.h"
#include "Node.h"
#include "NodeComparator.h"
using namespace std;

class SSSPAlgorithms {
public:
    void initial(int n, vector<Arc> inputArcs);

    void DijkstraWithBinaryHeap(int source);
    void Dial(int source);

    // Bellman Ford with Queue
    void SPFA(int source);

    // Bellman Ford with Dequeue
    void PAPE(int source);

    vector<int> getDis();
    vector<int> getPre();
    clock_t getProcessTime();
    int getRelaxNum();

private:
    vector<vector<Arc> > network;
    vector<int> dis;
    vector<int> pre;
    int nodeNum;

    clock_t processTime;
    int relaxNum;

    void reset();
    void vectorDelete(vector<int>& v, int value);
    int countMaxBucketSize();
    static bool arcCmp(Arc a1, Arc a2);
};

#endif
