#include "MinHeap.h"

MinHeap::MinHeap() {}

MinHeap::MinHeap(int size) { container.reserve(size); }

void MinHeap::push(Node node)
{
    container.push_back(node);
    decreaseValue(container.size() - 1, node);
}

void MinHeap::decreaseValue(int index, Node node)
{
    int parent = (index - 1) / 2;
    container[index] = node;
    while (index > 0 && container[parent] > container[index]) {
        swap(index, parent);
        index = parent;
        parent = (index - 1) / 2;
    }
}

void MinHeap::pop()
{
    container.erase(container.begin());
    minHeapify(0);
}

void MinHeap::minHeapify(int index)
{
    int left = 2 * (index + 1) - 1;
    int right = 2 * (index + 1);
    int size = container.size();
    int minIndex;

    if (left < size && container[left] < container[index])
        minIndex = left;
    else
        minIndex = index;

    if (right < size && container[right] < container[minIndex])
        minIndex = right;

    if (minIndex != index) {
        swap(minIndex, index);
        minHeapify(minIndex);
    }
}

void MinHeap::swap(int index1, int index2)
{
    Node tmp = container[index1];
    container[index1] = container[index2];
    container[index2] = tmp;
}

bool MinHeap::isEmpty() { return container.empty(); }

Node MinHeap::findMin() { return container.front(); }

int MinHeap::search(Node node)
{
    int index = -1;
    for (int i = 0; i < container.size(); i++)
        if (container[i] == node) {
            index = i;
            break;
        }
    return index;
}




