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
    void processData(double size, string filePath);
    

private:
    Triangulation triangulation;
    STLReader stlReader;
    
    StockMaterial mStockMaterial;
    VoxelGrid mStlVoxels;
};