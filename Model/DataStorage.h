#pragma once
#include "Point3D.h"
#include "Triangle.h"
#include "Triangulation.h"
#include "vector"
#include "STLReader.h"
#include "Visualizer.h"
#include "Voxel.h"
#include "Cylinder.h"
using namespace std;

class DataStorage
{
public:
    DataStorage(QMainWindow* parent);
    ~DataStorage();

    Triangulation triguObj;
    STLReader stlReaderObj;
    vector<Triangle> lot = triguObj.listOfTriangles();
    vector<Point3D> lop = triguObj.listOfPoints();
    
    
    
    Voxel* stockMaterial;
    Cylinder* drillTool;
    
    
};

