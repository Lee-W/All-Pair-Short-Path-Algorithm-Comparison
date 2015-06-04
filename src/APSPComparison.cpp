#include <iostream>
#include "SpFileReader.h"
#include "APSPAlgorithms.h"
#include "SSSPAlgorithms.h"
using namespace std;

void printUsage()
{
    cout << "Usage" << endl;
}

void checkCorectness(int nodeNum, vector<Arc> arcs)
{
    SSSPAlgorithms ssSPFA, ssDial, ssDij, ssPAPE;
    APSPAlgorithms apFWG, apFWA;

    ssSPFA.initial(nodeNum, arcs);
    ssDial.initial(nodeNum, arcs);
    ssDij.initial(nodeNum, arcs);
    ssPAPE.initial(nodeNum, arcs);
    apFWG.initial(nodeNum, arcs);
    apFWA.initial(nodeNum, arcs);

    apFWG.GraphicalFloydWarshall();
    apFWA.AlgebraicalFloydWarshall();

    vector<vector<int> > fwgDis = apFWG.getDis();
    vector<vector<int> > fwaDis = apFWA.getDis();
    vector<int> SPFADis, DialDis, dijDis, PAPEDis;
    // for (int i = 1; i < nodeNum+1; i++) {
    //     for (int j = 1; j < nodeNum+1; j++)
    //         cout << fwgDis[i][j] << "\t";
    //     cout << endl;
    // }
    // for (int i = 1; i < nodeNum+1; i++) {
        // for (int j = 1; j < nodeNum+1; j++)
            // cout << fwaDis[i][j] << "\t";
        // cout << endl;
    // }

    for (int i = 1; i < nodeNum+1; i++) {
    // for (int i = 1; i < 2; i++) {
        ssSPFA.SPFA(i);
        SPFADis = ssSPFA.getDis();

        ssDial.Dial(i);
        DialDis = ssDial.getDis();

        ssDij.DijkstraWithBinaryHeap(i);
        dijDis = ssDij.getDis();

        ssPAPE.PAPE(i);
        PAPEDis = ssPAPE.getDis();

        for (int j = 1; j < nodeNum + 1; j++) {
            // if (fwaDis[i][j] != SPFADis[j])
                // cout << "FWA SPFA Error " << fwaDis[i][j] << "\t" << SPFADis[j] << endl;
            // if (fwaDis[i][j] != PAPEDis[j])
                // cout << "FWA PAPE Error" << endl;
            if (fwaDis[i][j] != dijDis[j]) {
                cout << i << "\t" << j;
                cout << "FWA Dij Error " << fwaDis[i][j] << "\t" << dijDis[j] <<endl;
            }
            // if (fwaDis[i][j] != DialDis[j]) {
                // cout << i << "\t" << j;
                // cout << "FWA Dial Error " << fwaDis[i][j] << "\t" << DialDis[j] <<endl;
            // }
            // if (fwaDis[i][j] != fwgDis[i][j])
                // cout << "FWA FWG Error" << endl;
        }
        // cout << endl;
    }
    exit(0);
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

        checkCorectness(nodeNum, arcs);

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
