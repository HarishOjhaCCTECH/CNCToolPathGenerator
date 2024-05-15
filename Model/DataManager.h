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
    VoxelGrid& StlVoxels();

    void processData(double size, string filePath);

private:
    Triangulation triangulation;
    STLReader stlReader;
    StockMaterial* mStockMaterial;
    VoxelGrid* mStlVoxels;
};