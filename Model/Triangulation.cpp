#include "stdafx.h"
#include"Triangulation.h"
#include <vector>

Triangulation::Triangulation() {}
Triangulation::~Triangulation() {}

vector<Triangle>& Triangulation::listOfTriangles() { return mListOflistOfTriangles; }
vector<Point3D>& Triangulation::listOfPoints() { return mUniquelistOfPoints;}