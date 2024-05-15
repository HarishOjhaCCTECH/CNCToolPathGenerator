#pragma once
#include "Point3D.h"
#include "Triangle.h"
#include "StockMaterial.h"
#include "BoundingBox.h"
using namespace std;

class VoxelGrid
{
public:
	VoxelGrid();
	~VoxelGrid();

	QVector<GLfloat> GridVers();
	QVector<GLfloat> GridColrs();

	void stlVoxelFinding(vector<Point3D>& lop, BoundingBox box, double size);

private:
	vector<vector<vector<bool>>> mSTLGrid;
	QVector<GLfloat> mGridVertices;
	QVector<GLfloat> mGridColors;
};