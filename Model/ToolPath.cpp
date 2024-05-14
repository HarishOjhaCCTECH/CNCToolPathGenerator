#include "stdafx.h"
#include "ToolPath.h"

ToolPath::ToolPath() {}
ToolPath::ToolPath(const vector<vector<vector<BoundingBox>>>& boxes, const Point3D& toolStart)
{
	float cubeLen = 0;

	if (boxes.size() != 0) 
	{
		cubeLen = abs(boxes[0][0][0].Maxima().X() - boxes[0][0][0].Minima().X());
		mToolPathVertices << toolStart.X() << toolStart.Y() << toolStart.Z();

	}

	for (int i = boxes.size()-1; i >= 0; i--)
	{
		for (int j = boxes.at(0).size()-1; j >= 0; j--)
		{
			for (int k = boxes.at(0).at(0).size()-1; k >= 0; k--)
			{
				if (!boxes[i][j][k].existence())
				{
					mToolPathVertices << (boxes[i][j][k].Maxima().X() + boxes[i][j][k].Minima().X()) / 2;
					mToolPathVertices << (boxes[i][j][k].Maxima().Y() + boxes[i][j][k].Minima().Y()) / 2;
					mToolPathVertices << (boxes[i][j][k].Maxima().Z() + boxes[i][j][k].Minima().Z()) / 2;
				}
				else {
					int bhoot = 0;
					int newJ = BoxCheck(boxes, i, j + 1, k);
					mToolPathVertices << (boxes[i][newJ][k].Maxima().X() + boxes[i][newJ][k].Minima().X()) / 2;
					mToolPathVertices << ((boxes[i][newJ][k].Maxima().Y() + boxes[i][newJ][k].Minima().Y()) / 2) + cubeLen;
					mToolPathVertices << (boxes[i][newJ][k].Maxima().Z() + boxes[i][newJ][k].Minima().Z()) / 2;	
				}
				if (k == 0)
				{
					if (!boxes[i][j][k].existence())
					{
						mToolPathVertices << (boxes[i][j][k].Maxima().X() + boxes[i][j][k].Minima().X()) / 2;
						mToolPathVertices << ((boxes[i][j][k].Maxima().Y() + boxes[i][j][k].Minima().Y()) / 2) + cubeLen;
						mToolPathVertices << (boxes[i][j][k].Maxima().Z() + boxes[i][j][k].Minima().Z()) / 2;
					}
					mToolPathVertices << (boxes[i][j][9].Maxima().X() + boxes[i][j][9].Minima().X()) / 2;
					mToolPathVertices << ((boxes[i][j][9].Maxima().Y() + boxes[i][j][9].Minima().Y()) / 2) + cubeLen;
					mToolPathVertices << (boxes[i][j][9].Maxima().Z() + boxes[i][j][9].Minima().Z()) / 2;
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