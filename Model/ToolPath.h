#pragma once
#include "Voxel.h"
class ToolPath
{
public:

	ToolPath();
	ToolPath(const vector<vector<vector<BoundingBox>>>& boxes);
	~ToolPath();

	const QVector<GLfloat>& ToolPathVertices() const;
	const int BoxCheck(const vector<vector<vector<BoundingBox>>>& boxes, int i, int j, int k);

private:
	QVector<GLfloat> mToolPathVertices;
};

