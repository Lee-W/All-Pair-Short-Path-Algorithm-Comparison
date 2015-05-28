#include "APSPAlgorithms.h"

clock_t APSPAlgorithms::countTime(void (*func)())
{
    clock_t startTime = clock();
    (*func)();
    clock_t endTime = clock();
    return endTime - startTime;
}

void APSPAlgorithms::initial(int n, vector<Arc> inputArcs)
{
    arcs = inputArcs;

    nodeNum = n;
    dis.resize(nodeNum + 1);
    for (auto& row : dis)
        row.resize(nodeNum + 1, INF);
    for (int i = 0; i < dis.size(); i++)
        dis[i][i] = 0;

    pre.resize(nodeNum + 1);
    for (auto& row : pre)
        row.resize(nodeNum + 1, -1);

    for (auto arc : arcs) {
        dis[arc.from][arc.to] = arc.arcLength;
        pre[arc.from][arc.to] = arc.from;
    }
}

void APSPAlgorithms::AlgebraicalFloydWarshall()
{
    clock_t startTime = clock();
    relaxNum = 0;

    for (int mid = 1; mid < nodeNum + 1; mid++)
        for (int start = 0; start < nodeNum + 1; start++)
            for (int end = 0; end < nodeNum + 1; end++) {
                relaxNum++;
                if (dis[start][end] > dis[start][mid] + dis[mid][end]) {
                    dis[start][end] = dis[start][mid] + dis[mid][end];
                    pre[start][end] = pre[mid][end];
                }
            }

    processTime = clock() -startTime;
}

void APSPAlgorithms::GraphicalFloydWarshall()
{
    clock_t startTime = clock();
    relaxNum = 0;

    // GraphicalFloydWarshall initialization
    vector<vector<Arc> > fromList, toList;
    fromList.resize(nodeNum + 1);
    toList.resize(nodeNum + 1);
    for (auto arc: arcs) {
        fromList[arc.from].push_back(arc);
        toList[arc.to].push_back(arc);
    }

    for (int mid = 1; mid < nodeNum + 1; mid++)
    {
        for (auto startArc: toList[mid])
            for (auto endArc: fromList[mid]) {
                relaxNum++;

                int temp = startArc.arcLength + endArc.arcLength;
                if (dis[startArc.from][endArc.to] > temp) {
                    dis[startArc.from][endArc.to] = temp;
                    pre[startArc.from][endArc.to] = mid;
                }
            }
    }

    processTime = clock() -startTime;
}

clock_t APSPAlgorithms::getProcessTime()
{
    return processTime;
}

int APSPAlgorithms::getRelaxNum()
{
    return relaxNum;
}
