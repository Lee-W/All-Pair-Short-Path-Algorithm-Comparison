#include "SpFileReader.h"

SpFileReader::SpFileReader()
{
    nodeNum = -1;
    arcNum = -1;
}

// read file and parse each line by its identifier
void SpFileReader::readFile(string fileName)
{
    ifstream inputFileStream;
    inputFileStream.open(fileName);

    if (inputFileStream.is_open()) {
        int from, to;
        double arcLength;

        string line;
        while (getline(inputFileStream, line)) {
            vector<string> splitedLine = split(line);
            char identifier = splitedLine[0].at(0);
            switch (identifier) {
                case 'c':
                    // identifier c implies comment which should only be ignored
                    break;
                case 't':
                    problemName = splitedLine[1];
                    break;
                case 'p':
                    type = splitedLine[1];
                    nodeNum = stoi(splitedLine[2]);
                    arcNum = stoi(splitedLine[3]);

                    break;
                case 'n':
                    // ignore for sp file generator error
                    // nodeNum = stoi(splitedLine[1]);

                    break;
                case 'a':
                    from = stoi(splitedLine[1]);
                    to = stoi(splitedLine[2]);
                    arcLength = stod(splitedLine[3]);

                    arcs.push_back(Arc(from, to, arcLength));
                    break;
                default:
                    break;
            }
        }
        inputFileStream.close();
    }
    else {
        cout << "Cannot open file " << fileName << endl;
    }
}

// split string by space character
vector<string> SpFileReader::split(string str)
{
    vector<string> splitedStr;
    stringstream ss(str);
    string buf;
    while (ss >> buf)
        splitedStr.push_back(buf);

    return splitedStr;
}

string SpFileReader::getProblemName() { return problemName; }

string SpFileReader::getType() { return type; }

int SpFileReader::getNodeNum() { return nodeNum; }

int SpFileReader::getArcNum() { return arcNum; }

vector<Arc> SpFileReader::getArcs() { return arcs; }
