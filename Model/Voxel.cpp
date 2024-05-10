#include "stdafx.h"
#include "Voxel.h"

Voxel::Voxel() 
{
	int sizeX = 10;
	int sizeY = 10;
	int sizeZ = 10;
	boxes.resize(sizeX, std::vector<std::vector<BoundingBox>>(sizeY, std::vector<BoundingBox>(sizeZ)));
}

Voxel::Voxel(float xLen, float yLen, float zLen)
{
	int sizeX = 10;
	int sizeY = 10;
	int sizeZ = 10;
	boxes.resize(sizeX, std::vector<std::vector<BoundingBox>>(sizeY, std::vector<BoundingBox>(sizeZ)));

	int boxLimitPerAxis = 10;
	for (int k = 0; k < boxLimitPerAxis; k++)
	{
		for (int j = 0; j < boxLimitPerAxis; j++)
		{
			for (int i = 0; i < boxLimitPerAxis; i++)
			{
				float x_min = startPoint[0] + (i * xLen);
				float x_max = x_min + (xLen);

				float y_min = startPoint[1] + (j * yLen);
				float y_max = y_min + (yLen);

				float z_min = startPoint[2] + (k * zLen);
				float z_max = z_min + (zLen);
				
				boxes[i][j][k].minima.setX(x_min);
				boxes[i][j][k].minima.setY(y_min);
				boxes[i][j][k].minima.setZ(z_min);

				boxes[i][j][k].maxima.setX(x_max);
				boxes[i][j][k].maxima.setY(y_max);
				boxes[i][j][k].maxima.setZ(z_max);
				
				boxes[i][j][k].existence = false;

				//front
				mvertices1 << x_min << y_min << z_max;
				mvertices1 << x_max << y_min << z_max;
				mvertices1 << x_max << y_max << z_max;
				mvertices1 << x_min << y_max << z_max;
				mvertices1 << x_min << y_min << z_max;
				
				// back
				mvertices2 << x_min << y_min << z_min;
				mvertices2 << x_max << y_min << z_min;
				mvertices2 << x_max << y_max << z_min;
				mvertices2 << x_min << y_max << z_min;
				mvertices2 << x_min << y_min << z_min;

				// sides
				mvertices3 << x_min << y_min << z_max;
				mvertices3 << x_min << y_min << z_min;

				mvertices3 << x_max << y_min << z_max;
				mvertices3 << x_max << y_min << z_min;

				mvertices3 << x_max << y_max << z_max;
				mvertices3 << x_max << y_max << z_min;

				mvertices3 << x_min << y_max << z_max;
				mvertices3 << x_min << y_max << z_min;
			}
		}
	}
	
	for (int i = 0; i < 24; i++)
	{
		colors << 1 << 1 << 1;
	}
}

Voxel::~Voxel() {}

const QVector<GLfloat>& Voxel::getVertices1()
{
	return mvertices1;
}
const QVector<GLfloat>& Voxel::getVertices2()
{
	return mvertices2;
}
const QVector<GLfloat>& Voxel::getVertices3()
{
	return mvertices3;
}
const QVector<GLfloat>& Voxel::getColors()
{
	return colors;
}

const vector<vector<vector<BoundingBox>>>& Voxel::getBlocks()
{
	return boxes;
}
