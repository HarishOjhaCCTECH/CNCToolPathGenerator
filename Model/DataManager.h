#pragma once
#include "Triangulation.h"
#include "STLReader.h"
#include "Triangle.h"
#include "Point3D.h"
#include "StockMaterial.h"
#include "VoxelGrid.h"

class DataManager
{
public:
	DataManager();
	~DataManager();
    
    const StockMaterial& Stock() const;
    void processData(double size);
    

private:
    // read stl and find minima, maxima of stock material' bounding box
    Triangulation triguObj;
    STLReader stlReaderObj;
    vector<Triangle> lot = triguObj.listOfTriangles();
    vector<Point3D> lop = triguObj.listOfPoints();
    StockMaterial mStockMaterial;
    VoxelGrid mStlVoxels;
};