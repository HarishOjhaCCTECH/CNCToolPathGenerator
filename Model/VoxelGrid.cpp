#include "stdafx.h"
#include "VoxelGrid.h"

VoxelGrid::VoxelGrid() {}
VoxelGrid::~VoxelGrid() {}

QVector<GLfloat> VoxelGrid::GridVers() { return mGridVertices; }
QVector<GLfloat> VoxelGrid::GridColrs() { return mGridColors; }

void VoxelGrid::stlVoxelFinding(vector<Point3D>& lop, BoundingBox box, double size)
{
	int xDimension = int((box.Maxima().X() - box.Minima().X()) / size) + 1;
	int yDimension = int((box.Maxima().Y() - box.Minima().Y()) / size) + 1;
	int zDimension = int((box.Maxima().Z() - box.Minima().Z()) / size) + 1;
	mSTLGrid.resize(xDimension, vector<vector<bool>>(yDimension, vector<bool>(zDimension)));

	Point3D startPoint(box.Minima().X(), box.Minima().Y(), box.Minima().Z());

    for (auto& p : lop)
    {
		float px = p.X();
		float py = p.Y();
		float pz = p.Z();

		// For every point, looping through the mSTLGrid
		for (int i = 0; i < xDimension; i++)
		{
			for (int j = 0; j < yDimension; j++)
			{
				for (int k = 0; k < zDimension; k++)
				{
					float x_min = startPoint.X() + (i * size);
					float x_max = x_min + (size);

					float y_min = startPoint.Y() + (j * size);
					float y_max = y_min + (size);

					float z_min = startPoint.Z() + (k * size);
					float z_max = z_min + (size);


					if ((px >= x_min && px <= x_max) && (py >= y_min && py <= y_max) && (pz >= z_min && pz <= z_max))
					{
						mSTLGrid[i][j][k] = true;
						// front
						mGridVertices << x_min << y_min << z_max;
						mGridVertices << x_max << y_min << z_max;
						mGridVertices << x_max << y_max << z_max;
						mGridVertices << x_min << y_max << z_max;

						//back face
						mGridVertices << x_min << y_min << z_min;
						mGridVertices << x_max << y_min << z_min;
						mGridVertices << x_max << y_max << z_min;
						mGridVertices << x_min << y_max << z_min;

						// top
						mGridVertices << x_min << y_max << z_max;
						mGridVertices << x_max << y_max << z_max;
						mGridVertices << x_max << y_max << z_min;
						mGridVertices << x_min << y_max << z_min;

						//left of box
						mGridVertices << x_max << y_max << z_max;
						mGridVertices << x_max << y_min << z_max;
						mGridVertices << x_max << y_min << z_min;
						mGridVertices << x_max << y_max << z_min;

						// bottom
						mGridVertices << x_max << y_min << z_max;
						mGridVertices << x_min << y_min << z_max;
						mGridVertices << x_min << y_min << z_min;
						mGridVertices << x_max << y_min << z_min;

						// right of the box
						mGridVertices << x_min << y_min << z_max;
						mGridVertices << x_min << y_max << z_max;
						mGridVertices << x_min << y_max << z_min;
						mGridVertices << x_min << y_min << z_min;

						for (int ind = 0; ind < 24; ind++)
						{
							mGridColors << 1 << 0 << 0;
						}
					}
				}
			}
		}
    }
}