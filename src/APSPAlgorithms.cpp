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
    vector<map<int, Arc> > fromList, toList;
    fromList.resize(nodeNum + 1);
    toList.resize(nodeNum + 1);
    for (auto arc: arcs) {
        fromList[arc.from][arc.to] = arc;
        toList[arc.to][arc.from] = arc;
    }

    Arc startArc, endArc;
    for (int mid = 1; mid < nodeNum + 1; mid++)
        for (auto startArcEntry: toList[mid])
            for (auto endArcEntry: fromList[mid]) {
                startArc = startArcEntry.second;
                endArc = endArcEntry.second;

                relaxNum++;
                int temp = startArc.arcLength + endArc.arcLength;
                if (dis[startArc.from][endArc.to] > temp) {
                    fromList[startArc.from][endArc.to] = Arc(startArc.from, endArc.to, temp);
                    toList[endArc.to][startArc.from] = Arc(startArc.from, endArc.to, temp);

                    dis[startArc.from][endArc.to] = temp;
                    pre[startArc.from][endArc.to] = mid;
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
