#include <iostream>
#include "SpFileReader.h"
#include "APSPAlgorithms.h"
#include "SSSPAlgorithms.h"
using namespace std;

void printUsage()
{
    cout << "Usage" << endl;
}

int main(int argc, const char *argv[])
{
    int nodeNum;
    vector<Arc> arcs;

    if (argc == 2) {
        SpFileReader fr;
        fr.readFile(argv[1]);
        nodeNum = fr.getNodeNum();
        arcs = fr.getArcs();

        SSSPAlgorithms ss;
        APSPAlgorithms ap;
        ss.initial(nodeNum, arcs);
        ap.initial(nodeNum, arcs);

        int dialTime, dijkstraTime, PAPETime, SPFATime, GFWTime, AFWTime;
        int dialRelaxNum, dijkstraRelaxNum, PAPERelaxNum, SPFARelaxNum, GFWRelaxNum, AFWRelaxNum;

        for (int i = 1; i < nodeNum+1; i++) {
            ss.Dial(i);
            dialTime += ss.getProcessTime();
            dialRelaxNum += ss.getRelaxNum();

            ss.SPFA(i);
            SPFATime += ss.getProcessTime();
            SPFARelaxNum += ss.getRelaxNum();

            ss.DijkstraWithBinaryHeap(i);
            dijkstraTime += ss.getProcessTime();
            dijkstraRelaxNum += ss.getRelaxNum();


            ss.PAPE(i);
            PAPETime += ss.getProcessTime();
            PAPERelaxNum += ss.getRelaxNum();
        }

        ap.AlgebraicalFloydWarshall();
        GFWTime = ap.getProcessTime();
        GFWRelaxNum = ap.getRelaxNum();

        ap.GraphicalFloydWarshall();
        AFWTime = ap.getProcessTime();
        AFWRelaxNum = ap.getRelaxNum();

        cout << dialTime << "\t"
             << dijkstraTime << "\t"
             << SPFATime << "\t"
             << PAPETime << "\t" 
             << GFWTime << "\t"
             << AFWTime << endl;

        cout << dialRelaxNum << "\t"
             << dijkstraRelaxNum << "\t"
             << SPFARelaxNum << "\t"
             << PAPERelaxNum << "\t"
             << GFWRelaxNum << "\t"
             << AFWRelaxNum << endl;

        return 0;
    } else {
        printUsage();
    }
}
