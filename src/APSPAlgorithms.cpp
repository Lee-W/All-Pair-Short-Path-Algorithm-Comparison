#include "APSPAlgorithms.h"

bool APSPAlgorithms::arcCmp(Arc a1, Arc a2)
{
    if (a1.from == a2.from) {
        if (a1.to < a2.to)
            return a1.arcLength < a2.arcLength;
        return a1.to < a2.to;
    }
    return a1.from < a2.from;
}

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

    sort(arcs.begin(), arcs.end(), arcCmp);
    int preFrom = -1;
    int preTo = -1;
    for (auto arc : arcs) {
        if (arc.from == preFrom && arc.to == preTo)
            continue;
        else {
            dis[arc.from][arc.to] = arc.arcLength;
            pre[arc.from][arc.to] = arc.from;
            preFrom = arc.from;
            preTo = arc.to;
        }
    }
}

void APSPAlgorithms::AlgebraicalFloydWarshall()
{
    clock_t startTime = clock();
    relaxNum = 0;

    for (int mid = 1; mid < nodeNum + 1; mid++)
        for (int start = 1; start < nodeNum + 1; start++)
            for (int end = 1 ; end < nodeNum + 1; end++) {
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
                    if (dis[startArc.from][endArc.to] == INF) {
                        fromList[startArc.from].push_back(Arc(startArc.from, endArc.to, temp));
                        toList[endArc.to].push_back(Arc(startArc.from, endArc.to, temp));
                    }

                    dis[startArc.from][endArc.to] = temp;
                    pre[startArc.from][endArc.to] = mid;
                }
            }
    }

    processTime = clock() -startTime;
}

vector<vector<int> > APSPAlgorithms::getDis()
{
    return dis;
}

vector<vector<int> > APSPAlgorithms::getPre()
{
    return pre;
}

clock_t APSPAlgorithms::getProcessTime()
{
    return processTime;
}

int APSPAlgorithms::getRelaxNum()
{
    return relaxNum;
}
