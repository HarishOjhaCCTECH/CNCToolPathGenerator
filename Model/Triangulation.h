// this is header file for triangulation class declaration
// purpose - to store the points and triangles
#pragma once
#include <vector>
#include "Triangle.h"
#include "Point3D.h"
class Triangulation {
public:
    Triangulation(); // default constructor
    ~Triangulation(); // destructor
    std::vector<Triangle>& listOfTriangles();// getter
    std::vector<Point3D>& listOfPoints();//getter
private:
    std::vector<Triangle> mListOflistOfTriangles; // storage area for all the Triangles object
    std::vector<Point3D> mUniquelistOfPoints; // storage area for all the Points object
};