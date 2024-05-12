#include "stdafx.h"
#include "ToolPath.h"

ToolPath::ToolPath() {}
ToolPath::ToolPath(const vector<vector<vector<BoundingBox>>>& boxes)
{
	float cubeLen = abs(boxes[0][0][0].maxima().X() - boxes[0][0][0].minima().X());
	for (int i = 9; i >= 0; i--)
	{
		for (int j = 9; j >= 0; j--)
		{
			for (int k = 9; k >= 0; k--)
			{
				if (!boxes[i][j][k].existence())
				{
					mToolPathVertices << (boxes[i][j][k].maxima().X() + boxes[i][j][k].minima().X()) / 2;
					mToolPathVertices << (boxes[i][j][k].maxima().Y() + boxes[i][j][k].minima().Y()) / 2;
					mToolPathVertices << (boxes[i][j][k].maxima().Z() + boxes[i][j][k].minima().Z()) / 2;
				}
				else {
					int bhoot = 0;
					int newJ = BoxCheck(boxes, i, j + 1, k);
					mToolPathVertices << (boxes[i][newJ][k].maxima().X() + boxes[i][newJ][k].minima().X()) / 2;
					mToolPathVertices << ((boxes[i][newJ][k].maxima().Y() + boxes[i][newJ][k].minima().Y()) / 2) + cubeLen;
					mToolPathVertices << (boxes[i][newJ][k].maxima().Z() + boxes[i][newJ][k].minima().Z()) / 2;	
				}
				if (k == 0)
				{
					if (!boxes[i][j][k].existence())
					{
						mToolPathVertices << (boxes[i][j][k].maxima().X() + boxes[i][j][k].minima().X()) / 2;
						mToolPathVertices << ((boxes[i][j][k].maxima().Y() + boxes[i][j][k].minima().Y()) / 2) + cubeLen;
						mToolPathVertices << (boxes[i][j][k].maxima().Z() + boxes[i][j][k].minima().Z()) / 2;
					}
					mToolPathVertices << (boxes[i][j][9].maxima().X() + boxes[i][j][9].minima().X()) / 2;
					mToolPathVertices << ((boxes[i][j][9].maxima().Y() + boxes[i][j][9].minima().Y()) / 2) + cubeLen;
					mToolPathVertices << (boxes[i][j][9].maxima().Z() + boxes[i][j][9].minima().Z()) / 2;
				}
			}
		}
	}
}
ToolPath::~ToolPath() {}

const QVector<GLfloat>& ToolPath::ToolPathVertices() const { return mToolPathVertices; }

const int ToolPath::BoxCheck(const vector<vector<vector<BoundingBox>>>& boxes, int i, int j, int k)
{
	if (boxes[i][j][k].existence())
	{
		return BoxCheck(boxes, i, j + 1, k);
	}
	else {
		return j;
	}
}