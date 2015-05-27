#ifndef SP_FILE_READER_H
#define SP_FILE_READER_H

#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include "Arc.h"
using namespace std;

class SpFileReader {
public:
    SpFileReader();
    void readFile(string fileName);

    string getProblemName();
    string getType();
    int getNodeNum();
    int getArcNum();
    vector<Arc> getArcs();

private:
    string problemName;
    string type;
    int nodeNum;
    int arcNum;
    vector<Arc> arcs;

    vector<string> split(string);
};

#endif
