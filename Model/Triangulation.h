#pragma once
#include <vector>
#include "Triangle.h"
#include "Point3D.h"
using namespace std;

class Triangulation {
public:
    Triangulation();
    ~Triangulation();

    vector<Triangle>& listOfTriangles();
    vector<Point3D>& listOfPoints();

private:
    vector<Triangle> mListOflistOfTriangles;
    vector<Point3D> mUniquelistOfPoints;
};