#pragma once
#include "vector"
#include "BoundingBox.h"
#include "Point3D.h"
using namespace std;

class ToolPath
{
public:
	ToolPath();
	~ToolPath();

	QVector<GLfloat>& PathVertices();
	QVector<GLfloat>& PathColors();

	void findPath(vector<vector<vector<bool>>>& stl, BoundingBox box, double size);

private:
	void pathfinder(vector<vector<vector<bool>>>& stl, int i, int j, int k, double currentPathPointX, double currentPathPointY, double currentPathPointZ, double size, bool goneUp, bool goneDown, Point3D toolstart);
private:
	QVector<GLfloat> mPathVertices;
	QVector<GLfloat> mPathColors;
};