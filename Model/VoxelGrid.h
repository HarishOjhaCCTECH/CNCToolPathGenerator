#pragma once
#include "Point3D.h"
#include "Triangle.h"
#include "StockMaterial.h"
using namespace std;

class VoxelGrid
{
public:
	VoxelGrid();
	~VoxelGrid();
	void stlVoxelFinding(vector<Triangle>& lot, vector<Point3D>& lop, StockMaterial& stock);

private:
	vector<vector<vector<bool>>> mSTLGrid;
};