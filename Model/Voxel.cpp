#include "stdafx.h"
#include "Voxel.h"

Voxel::Voxel(){	boxLimitPerAxis = 10;}

Voxel::Voxel(float stlLargestModulusInteger, float distBetweenPoints)
{
	boxLimitPerAxis = stlLargestModulusInteger;

	int sizeX = boxLimitPerAxis;
	int sizeY = boxLimitPerAxis;
	int sizeZ = boxLimitPerAxis;	
	boxes.resize(sizeX, vector<vector<BoundingBox>>(sizeY, vector<BoundingBox>(sizeZ)));

	float startPoint[3]{- stlLargestModulusInteger ,-stlLargestModulusInteger ,-stlLargestModulusInteger };
	
	float xLen = distBetweenPoints / 2;
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
				
				boxes[i][j][k].setMinima(Point3D(x_min, y_min, z_min));

				boxes[i][j][k].setMaxima(Point3D(x_max, y_max, z_max));
				
				boxes[i][j][k].setExistence(false);

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
	
	for (int i = 0; i < 24; i++){colors << 1 << 1 << 1;}
}

Voxel::~Voxel() {}

void Voxel::stlVoxels(const vector<Triangle>& lot, const vector<Point3D>& lop)
{
	float triangleVertices[3][3];
	for (auto& k : lot)
	{
		triangleVertices[0][0] = lop[k.v1()].X();
		triangleVertices[0][1] = lop[k.v1()].Y();
		triangleVertices[0][2] = lop[k.v1()].Z();

		triangleVertices[1][0] = lop[k.v2()].X();
		triangleVertices[1][1] = lop[k.v2()].Y();
		triangleVertices[1][2] = lop[k.v2()].Z();

		triangleVertices[2][0] = lop[k.v3()].X();
		triangleVertices[2][1] = lop[k.v3()].Y();
		triangleVertices[2][2] = lop[k.v3()].Z();

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
						float x_min = boxes[i][j][k].Minima().X();
						float x_max = boxes[i][j][k].Maxima().X();
						float y_min = boxes[i][j][k].Minima().Y();
						float y_max = boxes[i][j][k].Maxima().Y();
						float z_min = boxes[i][j][k].Minima().Z();
						float z_max = boxes[i][j][k].Maxima().Z();

						if ((px >= x_min && px <= x_max) && (py >= y_min && py <= y_max) && (pz >= z_min && pz <= z_max))
						{
							boxes[i][j][k].setExistence(true);
							// front face
							mSTLVertices << x_min << y_min << z_max;
							mSTLVertices << x_max << y_min << z_max;
							mSTLVertices << x_max << y_max << z_max;
							mSTLVertices << x_min << y_max << z_max;

							//back face
							mSTLVertices << x_min << y_min << z_min;
							mSTLVertices << x_max << y_min << z_min;
							mSTLVertices << x_max << y_max << z_min;
							mSTLVertices << x_min << y_max << z_min;

							// top
							mSTLVertices << x_min << y_max << z_max;
							mSTLVertices << x_max << y_max << z_max;
							mSTLVertices << x_max << y_max << z_min;
							mSTLVertices << x_min << y_max << z_min;

							//left of box
							mSTLVertices << x_max << y_max << z_max;
							mSTLVertices << x_max << y_min << z_max;
							mSTLVertices << x_max << y_min << z_min;
							mSTLVertices << x_max << y_max << z_min;

							// bottom
							mSTLVertices << x_max << y_min << z_max;
							mSTLVertices << x_min << y_min << z_max;
							mSTLVertices << x_min << y_min << z_min;
							mSTLVertices << x_max << y_min << z_min;

							// right of the box
							mSTLVertices << x_min << y_min << z_max;
							mSTLVertices << x_min << y_max << z_max;
							mSTLVertices << x_min << y_max << z_min;
							mSTLVertices << x_min << y_min << z_min;
						}
					}
				}
			}
		}
	}
}

const QVector<GLfloat>& Voxel::getGridVertices1() const{return mGridVertices1;}
const QVector<GLfloat>& Voxel::getGridVertices2() const{return mGridVertices2;}
const QVector<GLfloat>& Voxel::getGridVertices3() const{return mGridVertices3;}
const QVector<GLfloat>& Voxel::getColors() const{return colors;}
const vector<vector<vector<BoundingBox>>>& Voxel::getBlocks() const{return boxes;}
const int& Voxel::getBoxLimitPerAxis() const { return boxLimitPerAxis; }
const QVector<GLfloat>& Voxel::getSTLVertices() const { return mSTLVertices; }