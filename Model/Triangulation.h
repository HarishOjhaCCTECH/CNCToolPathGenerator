#pragma once
#include "Triangle.h"
#include "Point3D.h"

using namespace std;

class Triangulation
{
public:
	Triangulation();
	~Triangulation();

    const vector<Triangle>& listOfTriangles() const;
    const vector<Point3D>& listOfPoints() const;

private:
    vector<Triangle> mListOflistOfTriangles;
    vector<Point3D> mUniquelistOfPoints;
};