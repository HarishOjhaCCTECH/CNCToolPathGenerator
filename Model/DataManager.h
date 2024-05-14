#pragma once
#include "Point3D.h"
#include "Triangle.h"
#include "Triangulation.h"
#include "vector"
#include "STLReader.h"
#include "Visualizer.h"
#include "Voxel.h"
#include "ToolCylinder.h"
#include "ToolPath.h"
#include "ToolPathTxtWriter.h"

using namespace std;

class DataManager
{
public:
    DataManager(QMainWindow* parent);
    ~DataManager();

    const Voxel& stockMaterial();
    const ToolCylinder& toolCylinder();
    const ToolPath& generatedToolPath();

    
    void setToolSize(const float& inFloat);
    void processData(string path);
    void simulate();
    void savefile();

private:
    Triangulation triguObj;
    STLReader stlReaderObj;
    vector<Triangle> lot = triguObj.listOfTriangles();
    vector<Point3D> lop = triguObj.listOfPoints();   
    Voxel* mStockMaterial;
    ToolCylinder* mToolCylinder;
    ToolPath* mGeneratedToolPath;
    const char* mShapeFilePath = "";
    float mToolSize = 0;
    Point3D mToolStartPoint;
    ToolPathTxtWriter* mToolPathTxt;
};

