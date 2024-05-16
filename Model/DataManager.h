#pragma once
#include "Triangulation.h"
#include "STLReader.h"
#include "Triangle.h"
#include "Point3D.h"
#include "string"
#include "StockMaterial.h"
#include "VoxelGrid.h"
#include "ToolPath.h"
#include "ToolCylinder.h"
using namespace std;

class DataManager
{
public:
    DataManager();
    ~DataManager();

    StockMaterial& Stock();
    VoxelGrid& StlVoxels();
    ToolPath& Path();
    ToolCylinder& Tool();

    void processData(double size, string filePath);
    void simulate(double size, int position);

private:
    Triangulation triangulation;
    STLReader stlReader;
    StockMaterial* mStockMaterial;
    VoxelGrid* mStlVoxels;
    ToolPath* mPath;
    ToolCylinder* mTool;
};