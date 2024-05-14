#pragma once
#include "Point3D.h"
#include "StockMaterial.h"
using namespace std;
class STLVoxel
{
public:
	STLVoxel();
	~STLVoxel();
	void stlVoxelFinding(vector<Point3D>& lop, StockMaterial& stock);

private:
	vector<vector<vector<bool>>> mSTLGrid;
};
