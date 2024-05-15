#pragma once
#include "Triangulation.h"
#include "STLReader.h"
#include "Triangle.h"
#include "Point3D.h"
#include "string"
#include "StockMaterial.h"
#include "VoxelGrid.h"
using namespace std;
class DataManager
{
public:
    DataManager();
    ~DataManager();

    StockMaterial& Stock();
    void processData(double size, string filePath);
    VoxelGrid& StlVoxels();

private:
    Triangulation triangulation;
    STLReader stlReader;
    //STLReader stlReader;
  //  vector<Point3D> lop = triangulation.listOfPoints();
//    vector<Triangle> lot = triangulation.listOfTriangles();

    StockMaterial* mStockMaterial;
    VoxelGrid* mStlVoxels;
};