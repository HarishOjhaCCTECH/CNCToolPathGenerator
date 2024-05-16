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
	QVector<GLfloat> mPathVertices;
	QVector<GLfloat> mPathColors;
};