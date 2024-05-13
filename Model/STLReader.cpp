#include "stdafx.h"
#include "STLReader.h"
#include "map"
#include "Point3D.h"
#include "fstream"
#include <iostream>
#include "Triangle.h"

using namespace std;

STLReader::STLReader() {}
STLReader::~STLReader() {}

void STLReader::read(const string& stlFilePath, vector<Triangle>& lot, vector<Point3D>& lop)
{
    map<Point3D, int> comparisonMap;
    ifstream stlFile;
    string stlLine;
    stlFile.open(stlFilePath);
    if (!stlFile.is_open()) {
        cerr << "Error opening file!" << endl;
    }

    int triangleIndices[3] = { 0,0,0 };
    int triangleIndicesCurrentIndex = 0;
    int lopCurrentIndex = 0;
    
    while (getline(stlFile, stlLine)) {
        int positionVertex = stlLine.find("vertex ");
        int positionEndLoop = stlLine.find("endloop");
        if (positionVertex != string::npos) {
            string str = stlLine.substr(positionVertex + 7);
            double threeCoordinatesArr[3] = { 0,0,0 };
            for (int i = 0; i < 3; i++) {
                int pos3 = str.find(" ");
                threeCoordinatesArr[i] = stod(str.substr(0, pos3));
                str = str.substr(pos3 + 1);
            }

           
            bool foundPoint = false;
            for (const auto& i : comparisonMap) {
                if ((i.first.X() == threeCoordinatesArr[0]) && (i.first.Y() == threeCoordinatesArr[1]) && (i.first.Z() == threeCoordinatesArr[2])) {
                    triangleIndices[triangleIndicesCurrentIndex] = i.second;
                    triangleIndicesCurrentIndex++;
                    foundPoint = true;
                    break;
                }
            }
            if (!foundPoint) {
                lop.emplace_back(threeCoordinatesArr[0], threeCoordinatesArr[1], threeCoordinatesArr[2]);
                comparisonMap[Point3D(threeCoordinatesArr[0], threeCoordinatesArr[1], threeCoordinatesArr[2])] = lopCurrentIndex;
                triangleIndices[triangleIndicesCurrentIndex] = lopCurrentIndex;
                lopCurrentIndex++;
                triangleIndicesCurrentIndex++;
            }
        }

        if (positionEndLoop != string::npos) {
            lot.emplace_back(triangleIndices[0], triangleIndices[1], triangleIndices[2]);
            triangleIndicesCurrentIndex = 0;
        }
    }
}