#ifndef MIN_HEAP_H
#define MIN_HEAP_H

#include <vector>
#include "Node.h"
using namespace std;

class MinHeap {
public:
    MinHeap();
    MinHeap(int size);

    void push(Node node);
    void pop();
    void decreaseValue(int index, Node node);
    Node findMin();
    int search(Node node);
    bool isEmpty();
private:
    vector<Node> container;

    void swap(int index1, int index2);
    void minHeapify(int index);
};

#endif
