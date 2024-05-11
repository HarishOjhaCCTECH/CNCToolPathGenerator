#include "stdafx.h"
#include "Voxel.h"

Voxel::Voxel() 
{
	boxLimitPerAxis = 10;
}

Voxel::Voxel(float stlLargestModulusInteger, float distBetweenPoints)
{
	
	boxLimitPerAxis = stlLargestModulusInteger * 2;
	//boxLimitPerAxis = inBoxLimitPerAxis;
	int sizeX = boxLimitPerAxis;
	int sizeY = boxLimitPerAxis;
	int sizeZ = boxLimitPerAxis;
	
	boxes.resize(sizeX, vector<vector<BoundingBox>>(sizeY, vector<BoundingBox>(sizeZ)));

	float startPoint[3]{- stlLargestModulusInteger ,-stlLargestModulusInteger ,-stlLargestModulusInteger };
	//startPoint[0] = -stlLargestModulusInteger;
	//startPoint[1] = -stlLargestModulusInteger;
	//startPoint[2] = -stlLargestModulusInteger;
	
	float xLen = distBetweenPoints/2;
	float yLen = distBetweenPoints / 2;
	float zLen = distBetweenPoints / 2;

	for (int i = 0; i < boxLimitPerAxis; i++)
	{
		for (int j = 0; j < boxLimitPerAxis; j++)
		{
			for (int k = 0; k < boxLimitPerAxis; k++)
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
				mGridVertices1 << x_min << y_min << z_max;
				mGridVertices1 << x_max << y_min << z_max;
				mGridVertices1 << x_max << y_max << z_max;
				mGridVertices1 << x_min << y_max << z_max;
				mGridVertices1 << x_min << y_min << z_max;
				
				// back
				mGridVertices2 << x_min << y_min << z_min;
				mGridVertices2 << x_max << y_min << z_min;
				mGridVertices2 << x_max << y_max << z_min;
				mGridVertices2 << x_min << y_max << z_min;
				mGridVertices2 << x_min << y_min << z_min;

				// sides
				mGridVertices3 << x_min << y_min << z_max;
				mGridVertices3 << x_min << y_min << z_min;

				mGridVertices3 << x_max << y_min << z_max;
				mGridVertices3 << x_max << y_min << z_min;

				mGridVertices3 << x_max << y_max << z_max;
				mGridVertices3 << x_max << y_max << z_min;

				mGridVertices3 << x_min << y_max << z_max;
				mGridVertices3 << x_min << y_max << z_min;
			}
		}
	}
	
	for (int i = 0; i < 24; i++)
	{
		colors << 1 << 1 << 1;
	}
}

Voxel::~Voxel() {}

const QVector<GLfloat>& Voxel::getGridVertices1()
{
	return mGridVertices1;
}
const QVector<GLfloat>& Voxel::getGridVertices2()
{
	return mGridVertices2;
}
const QVector<GLfloat>& Voxel::getGridVertices3()
{
	return mGridVertices3;
}
const QVector<GLfloat>& Voxel::getColors()
{
	return colors;
}

const vector<vector<vector<BoundingBox>>>& Voxel::getBlocks()
{
	return boxes;
}


void Voxel::stlVoxels(const vector<Triangle>& lot, const vector<Point3D>& lop)
{
	int numOfStlBoxes = 0;
	int numboxesSTL2= 0;
	int temp = 0;
	float triangleVertices[3][3];
	for (auto& k : lot) {
		triangleVertices[0][0] = lop[k.v1()].X();
		triangleVertices[0][1] = lop[k.v1()].Y();
		triangleVertices[0][2] = lop[k.v1()].Z();


		triangleVertices[1][0] = lop[k.v2()].X();
		triangleVertices[1][1] = lop[k.v2()].Y();
		triangleVertices[1][2] = lop[k.v2()].Z();
		
		triangleVertices[2][0] = lop[k.v3()].X();
		triangleVertices[2][1] = lop[k.v3()].Y();
		triangleVertices[2][2] = lop[k.v3()].Z();

		
		
		// checking points from stl, rendering 
		
		for (int l = 0; l < 3; l++)
		{
			for (int i = 0; i < boxLimitPerAxis; i++)
			{
				for (int j = 0; j < boxLimitPerAxis; j++)
				{
					for (int k = 0; k < boxLimitPerAxis; k++)
					{
						float px = triangleVertices[l][0];
						float py = triangleVertices[l][1];
						float pz = triangleVertices[l][2];
						float xMin = boxes[i][j][k].minima.X();
						float xMax = boxes[i][j][k].maxima.X();
						float yMin = boxes[i][j][k].minima.Y();
						float yMax = boxes[i][j][k].maxima.Y();
						float zMin = boxes[i][j][k].minima.Z();
						float zMax = boxes[i][j][k].maxima.Z();

						if ((px >= xMin && px <= xMax) && (py >= yMin && py <= yMax) && (pz >= zMin && pz <= zMax))
						{
							boxes[i][j][k].existence = true;
							numOfStlBoxes++;
						}
						temp++;
					}
				}
			}
		}
		
		
	}
	
	for (int i = 0; i < boxLimitPerAxis; i++)
	{
		for (int j = 0; j < boxLimitPerAxis; j++)
		{
			for (int k = 0; k < boxLimitPerAxis; k++)
			{
				if (boxes[i][j][k].existence)
				{
					float x_min = boxes[i][j][k].minima.X();
					float x_max = boxes[i][j][k].maxima.X();

					float y_min = boxes[i][j][k].minima.Y();
					float y_max = boxes[i][j][k].maxima.Y();

					float z_min = boxes[i][j][k].minima.Z();
					float z_max = boxes[i][j][k].maxima.Z();
					//front
					mSTLVertices1<< x_min << y_min << z_max;
					mSTLVertices1 << x_max << y_min << z_max;
					mSTLVertices1 << x_max << y_max << z_max;
					mSTLVertices1 << x_min << y_max << z_max;
					mSTLVertices1 << x_min << y_min << z_max;

					//back
					mSTLVertices2 << x_min << y_min << z_min;
					mSTLVertices2 << x_max << y_min << z_min;
					mSTLVertices2 << x_max << y_max << z_min;
					mSTLVertices2 << x_min << y_max << z_min;
					mSTLVertices2 << x_min << y_min << z_min;

					// sides
					mSTLVertices3 << x_min << y_min << z_max;
					mSTLVertices3 << x_min << y_min << z_min;

					mSTLVertices3 << x_max << y_min << z_max;
					mSTLVertices3 << x_max << y_min << z_min;

					mSTLVertices3 << x_max << y_max << z_max;
					mSTLVertices3 << x_max << y_max << z_min;

					mSTLVertices3 << x_min << y_max << z_max;
					mSTLVertices3 << x_min << y_max << z_min;
					numboxesSTL2++;
				}


				
			}
		}
	}
	int yi = 0;
	
}

const QVector<GLfloat>& Voxel::getSTLVertices1()
{
	return mSTLVertices1;
}
const QVector<GLfloat>& Voxel::getSTLVertices2()
{
	return mSTLVertices2;
}
const QVector<GLfloat>& Voxel::getSTLVertices3()
{
	return mSTLVertices3;
}

const int& Voxel::getBoxLimitPerAxis() { return boxLimitPerAxis; }