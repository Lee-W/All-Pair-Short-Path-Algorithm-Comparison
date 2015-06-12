#include <fstream>
#include <stdio.h>
#include "SpFileReader.h"
#include "APSPAlgorithms.h"
#include "SSSPAlgorithms.h"
using namespace std;

void readSPFile(string fileName);
void setIterationNum(int nIt);
void init();
void runSPAlgorithms();
void averageTime();
void averageRelaxNum();
void printSummary(int numLen = 10);
void printUsage();
void exportToCSV(string fileName = "Report.csv");
void checkCorrectness(int nodeNum, vector<Arc> arcs);

int nodeNum;
vector<Arc> arcs;
int dialTime, dijkstraTime, PAPETime, SPFATime, GFWTime, AFWTime;
int dialRelaxNum, dijkstraRelaxNum, PAPERelaxNum, SPFARelaxNum,
    GFWRelaxNum, AFWRelaxNum;

int iterationNum;

string titleOutputSeq[6] = {"Dial", "Dijkstra", "SPFA", "PAPE", "GFW", "AFW"};

int main(int argc, const char *argv[])
{
    if (argc > 2) {
        readSPFile(argv[1]);

        if (argc == 4)
            setIterationNum(stoi(argv[3]));
        else
            setIterationNum(1);

        init();
        for (int i = 0; i < iterationNum; i++)
            runSPAlgorithms();
        averageTime();
        averageRelaxNum();

        printSummary();

        printf("Export to %s", argv[2]);
        exportToCSV(argv[2]);

        return 0;
    }
    else {
        printUsage();
    }
}

void readSPFile(string fileName)
{
    SpFileReader fr;
    fr.readFile(fileName);
    nodeNum = fr.getNodeNum();
    arcs = fr.getArcs();
}

void setIterationNum(int nIt) { iterationNum = nIt; }

void init()
{
    dialTime = 0;
    dijkstraTime = 0;
    PAPETime = 0;
    SPFATime = 0;
    GFWTime = 0;
    AFWTime = 0;

    dialRelaxNum = 0;
    dijkstraRelaxNum = 0;
    PAPERelaxNum = 0;
    SPFATime = 0;
    GFWRelaxNum = 0;
    AFWRelaxNum = 0;
}

void runSPAlgorithms()
{
    SSSPAlgorithms ss;
    APSPAlgorithms ap;
    ss.initial(nodeNum, arcs);
    ap.initial(nodeNum, arcs);

    for (int i = 1; i < nodeNum + 1; i++) {
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

    ap.GraphicalFloydWarshall();
    GFWTime += ap.getProcessTime();
    GFWRelaxNum += ap.getRelaxNum();

    ap.AlgebraicalFloydWarshall();
    AFWTime += ap.getProcessTime();
    AFWRelaxNum += ap.getRelaxNum();
}

void averageTime()
{
    dialTime /= iterationNum;
    dijkstraTime /= iterationNum;
    PAPETime /= iterationNum;
    SPFATime /= iterationNum;
    GFWTime /= iterationNum;
    AFWTime /= iterationNum;
}

void averageRelaxNum()
{
    dialRelaxNum /= iterationNum;
    dijkstraRelaxNum /= iterationNum;
    PAPERelaxNum /= iterationNum;
    SPFARelaxNum /= iterationNum;
    GFWRelaxNum /= iterationNum;
    AFWRelaxNum /= iterationNum;
}

void printSummary(int numLen)
{
    string titleFormatStr = "%12s";
    string valueFormatStr = "%-12s";

    for (int i = 0; i < 6; i++) {
        titleFormatStr += "%" + to_string(numLen) + "s";
        valueFormatStr += "%" + to_string(numLen) + "d";
    }
    titleFormatStr += "\n";
    valueFormatStr += "\n";

    printf(titleFormatStr.c_str(), "", "Dial", "Dijkstra", "SPFA", "PAPE",
           "GFW", "AFW");
    printf(valueFormatStr.c_str(), "Time:", dialTime, dialTime, SPFATime,
           PAPETime, GFWTime, AFWTime);
    printf(valueFormatStr.c_str(), "Relax Num:", dialRelaxNum, dialRelaxNum,
           SPFARelaxNum, PAPERelaxNum, GFWRelaxNum, AFWRelaxNum);
}

void exportToCSV(string fileName)
{
   ofstream outputFileStream(fileName, ofstream::out | ofstream::app);
   if (outputFileStream.is_open()) {
       outputFileStream << "" << ",";
       for (auto title : titleOutputSeq)
           outputFileStream << title << ",";
       outputFileStream << "\n";

       outputFileStream << "Time" << ","
                        << dialTime << ","
                        << dijkstraTime << ","
                        << SPFATime << ","
                        << PAPETime << ","
                        << GFWTime << ","
                        << AFWTime << "," << "\n";

       outputFileStream << "Relax Num" << ","
                        << dialRelaxNum << ","
                        << dijkstraRelaxNum << ","
                        << SPFARelaxNum << ","
                        << PAPERelaxNum << ","
                        << GFWTime << ","
                        << AFWRelaxNum << "," << "\n";
   } else {
       printf("Cannot open file %s ", fileName.c_str());
   }
}

void printUsage()
{
    printf("Usage:\n");
    printf("\t./bin/SPSPComparison.out \"input sp file\" \"output file name\" [n_it] \n");
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

    vector<vector<int>> fwgDis = apFWG.getDis();
    vector<vector<int>> fwaDis = apFWA.getDis();
    vector<int> SPFADis, DialDis, dijDis, PAPEDis;

    for (int i = 1; i < nodeNum + 1; i++) {
        ssSPFA.SPFA(i);
        SPFADis = ssSPFA.getDis();

        ssDial.Dial(i);
        DialDis = ssDial.getDis();

        ssDij.DijkstraWithBinaryHeap(i);
        dijDis = ssDij.getDis();

        ssPAPE.PAPE(i);
        PAPEDis = ssPAPE.getDis();

        for (int j = 1; j < nodeNum + 1; j++) {
            if (fwaDis[i][j] != SPFADis[j])
                cout << "FWA SPFA Error " << fwaDis[i][j] << "\t" << SPFADis[j]
                     << endl;
            if (fwaDis[i][j] != PAPEDis[j])
                cout << "FWA PAPE Error" << endl;
            if (fwaDis[i][j] != dijDis[j])
                cout << " FWA Dij Error " << fwaDis[i][j] << "\t" << dijDis[j]
                     << endl;
            if (fwaDis[i][j] != DialDis[j])
                cout << " FWA Dial Error " << fwaDis[i][j] << "\t" << DialDis[j]
                     << endl;
            if (fwaDis[i][j] != fwgDis[i][j])
                cout << "FWA FWG Error" << endl;
        }
        // cout << endl;
    }
    exit(0);
}
