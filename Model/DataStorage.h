#pragma once
#include "Point3D.h"
#include "Triangle.h"
#include "Triangulation.h"
#include "vector"
#include "STLReader.h"
#include "Visualizer.h"
#include "Voxel.h"
#include "Cylinder.h"
#include "ToolPath.h"

using namespace std;

class DataStorage
{
public:
    DataStorage(QMainWindow* parent);
    ~DataStorage();

    const Voxel& stockMaterial();
    const Cylinder& toolCylinder();
    const ToolPath& generatedToolPath();

    void setShapeFilePath(const char* inChar);
    void setToolSize(const float& inFloat);
    void processData();

private:
    Triangulation triguObj;
    STLReader stlReaderObj;
    vector<Triangle> lot = triguObj.listOfTriangles();
    vector<Point3D> lop = triguObj.listOfPoints();   
    Voxel* mStockMaterial;
    Cylinder* mToolCylinder;
    ToolPath* mGeneratedToolPath;
    const char* mShapeFilePath = "";
    float mToolSize;
};

