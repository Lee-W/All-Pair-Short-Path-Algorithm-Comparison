#include "SSSPAlgorithms.h"

void SSSPAlgorithms::initial(int n, vector<Arc> arcs)
{
    nodeNum = n;
    dis.resize(nodeNum + 1, INF);
    pre.resize(nodeNum + 1, -1);

    network.resize(nodeNum + 1);

    for (auto arc : arcs)
        network[arc.from].push_back(arc);
}

void SSSPAlgorithms::DijkstraWithBinaryHeap(int source)
{
    clock_t startTime = clock();
    relaxNum = 0;

    MinHeap h;
    dis[source] = 0;
    pre[source] = source;
    h.push(Node(source, dis[source]));

    Node heapTop;
    int tempDis;
    int index;
    while (!h.isEmpty()) {
        heapTop = h.findMin();
        h.pop();

        // Relaxation
        for (auto i : network[heapTop.index]) {
            relaxNum++;

            tempDis = dis[heapTop.index] + i.arcLength;
            if (tempDis < dis[i.to]) {
                if (dis[i.to] == INF)
                    h.push(Node(i.to, dis[i.to]));
                else {
                    index = h.search(Node(i.to, dis[i.to]));
                    h.decreaseValue(index, Node(i.to, tempDis));
                }
                dis[i.to] = tempDis;
                pre[i.to] = heapTop.index;
            }
        }
    }
    processTime = clock() - startTime;
}

void SSSPAlgorithms::Dial(int source)
{
    clock_t startTime = clock();
    relaxNum = 0;

    vector<vector<int> > indexBucket;
    int maxBucketSize = countMaxBucketSize();
    indexBucket.resize(maxBucketSize);

    dis[source] = 0;
    pre[source] = source;
    indexBucket.resize(dis[source] + 1);
    indexBucket[dis[source]].push_back(source);

    int curMin = 0;
    int curNodeIndex;
    int tempDis;
    bool changeOccur = true;
    while (changeOccur) {
        changeOccur = false;

        // Find next node to relax
        for (int i = curMin; i < indexBucket.size(); i++)
            if (!indexBucket[i].empty()) {
                curNodeIndex = indexBucket[i].back();
                indexBucket[i].pop_back();
                curMin = i;
                break;
            }

        // Relaxation
        for (auto i : network[curNodeIndex]) {
            relaxNum++;

            tempDis = dis[curNodeIndex] + i.arcLength;
            if (tempDis < dis[i.to]) {
                // In case that bucket is not large enough
                if (tempDis > indexBucket.size())
                    indexBucket.resize(tempDis + 1);

                // Update value in bucket
                if (dis[i.to] != INF)
                    vectorDelete(indexBucket[dis[i.to]], i.to);

                indexBucket[tempDis].push_back(i.to);

                dis[i.to] = tempDis;
                pre[i.to] = curNodeIndex;
                changeOccur = true;
            }
        }
    }
    processTime = clock() - startTime;
}

// Count the sum of the first ecountered numbers since bucket size would never
// be large than it
int SSSPAlgorithms::countMaxBucketSize()
{
    int maxBucketSize = 0;

    int counter = 0;
    for (auto i : network) {
        for (auto j : i) {
            maxBucketSize += j.arcLength;
            counter++;
        }
        if (counter > nodeNum)
            break;
    }
    return maxBucketSize;
}

void SSSPAlgorithms::vectorDelete(vector<int>& v, int value)
{
    v.erase(remove(v.begin(), v.end(), value), v.end());
}

// Bellman Ford with Dequeue
void SSSPAlgorithms::PAPE(int source)
{
    clock_t startTime = clock();
    relaxNum = 0;

    processTime = clock() - startTime;
}

// Bellman Ford with Queue
void SSSPAlgorithms::SPFA(int source)
{
    clock_t startTime = clock();
    relaxNum = 0;

    queue<int> q;
    vector<bool> inqueue(nodeNum + 1, false);

    dis[source] = 0;
    inqueue[source] = true;
    q.push(source);

    while (!q.empty()) {
        int cur = q.front();
        inqueue[cur] = false;
        q.pop();

        for (auto arc : network[cur]) {
            int des = arc.to;
            int len = arc.arcLength;

            relaxNum++;
            if (dis[cur] + len < dis[des]) {
                dis[des] = dis[cur] + len;
                pre[des] = cur;
                q.push(des);
                inqueue[des];
            }
        }
    }
    processTime = clock() - startTime;
}

vector<int> SSSPAlgorithms::getDis()
{
    return dis;
}

vector<int> SSSPAlgorithms::getPre()
{
    return pre;
}

clock_t SSSPAlgorithms::getProcessTime()
{
    return processTime;
}

int SSSPAlgorithms::getRelaxNum()
{
    return relaxNum;
}
