#include "stdafx.h"
#include"Triangulation.h"
#include <vector>
Triangulation::Triangulation() {} // default constructor
Triangulation::~Triangulation() {} // destructor
std::vector<Triangle>& Triangulation::listOfTriangles() { // getter
    return mListOflistOfTriangles;
}
std::vector<Point3D>& Triangulation::listOfPoints() { // getter
    return mUniquelistOfPoints;
}