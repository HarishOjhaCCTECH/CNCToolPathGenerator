#include "stdafx.h"
#include "ToolPath.h"

ToolPath::ToolPath() {}
ToolPath::~ToolPath() {}

QVector<GLfloat>& ToolPath::PathVertices() { return mPathVertices; }
QVector<GLfloat>& ToolPath::PathColors() { return mPathColors; }

void ToolPath::findPath(vector<vector<vector<bool>>>& stl, BoundingBox box, double size)
{
	mPathVertices.clear();
	mPathColors.clear();
	bool upAndDown = false;
	int prevHeight = 0;
	int maxHeight = 0;
	int xDimension = int((box.Maxima().X() - box.Minima().X()) / size) + 1;
	int yDimension = int((box.Maxima().Y() - box.Minima().Y()) / size) + 2;
	int zDimension = int((box.Maxima().Z() - box.Minima().Z()) / size) + 2;

	Point3D stockStartPoint(box.Minima().X(), box.Minima().Y(), box.Minima().Z());

	for (int i = xDimension - 1; i >= 0; i--)
	{
		for (int j = yDimension - 1; j >= 0; j--)
		{
			// tool start point
			double toolStartX = (stockStartPoint.X() + (i * size) + size) / 2;
			double toolStartY = (stockStartPoint.Y() + (j * size) + size) / 2;
			double toolStartZ =( (stockStartPoint.Z() + ((zDimension-1) * size))+size)/2 + (5*size);

			Point3D toolStartPoint(toolStartX, toolStartY, toolStartZ);
			mPathVertices << toolStartX << toolStartY << toolStartZ;
			mPathColors << 0.9844 << 0.7578 << 0.0117;
			
			for (int k = zDimension-1; k >=0; k--)
			{
				float x_min = stockStartPoint.X() + (i * size);
				float x_max = x_min + (size);

				float y_min = stockStartPoint.Y() + (j * size);
				float y_max = y_min + (size);

				float z_min = stockStartPoint.Z() + (k * size);
				float z_max = z_min + (size);

				float currentPathPointX = (x_min + x_max) / 2;
				float currentPathPointY = (y_min + y_max) / 2;
				float currentPathPointZ = (z_min + z_max) / 2;
								
				if (!stl[i][j][k]) { // execute it when non stlcubes are encountered

					if (upAndDown) // to check previous path deviation
					{
						mPathVertices << currentPathPointX << currentPathPointY+size << currentPathPointZ;
						mPathColors << 0.9844 << 0.7578 << 0.0117;
					}
					mPathVertices << currentPathPointX << currentPathPointY << currentPathPointZ;
					mPathColors << 0.9844 << 0.7578 << 0.0117;
					upAndDown = false;
				}
				else
				{   
					int currentHeight = 0;
					int currentJpos = j;
					currentJpos++;
					while (stl[i][currentJpos][k]) { // checking the height of stlcubes above the current stlcube
						currentJpos++;
					}
					currentHeight = currentJpos - j;
					if (currentHeight > prevHeight) // climb around the stlcubes
					{
						for (int toolsteps = 1; toolsteps <= (currentJpos - j); toolsteps++) {
							if (!stl[i][j + toolsteps][k + 1])
							{
								mPathVertices << currentPathPointX << currentPathPointY + (size * toolsteps) << currentPathPointZ + size;
								mPathColors << 0.9844 << 0.7578 << 0.0117;
							}
						}
						mPathVertices << currentPathPointX << currentPathPointY + (size * (currentJpos - j)) << currentPathPointZ;
						mPathColors << 0.9844 << 0.7578 << 0.0117;
					}
					else if (currentHeight<prevHeight) // plunge around the stlcubes
					{
						QVector<GLfloat> tempVertices;
						for (int toolsteps = prevHeight; toolsteps >= currentHeight; toolsteps--)
						{
							mPathVertices << currentPathPointX << currentPathPointY + (size * (toolsteps - j)) << currentPathPointZ;
						}
					}
					else // continuous straight path over stlcubes
					{
						mPathVertices << currentPathPointX << currentPathPointY + (size * (currentHeight-j)) << currentPathPointZ;
						mPathColors << 0.9844 << 0.7578 << 0.0117;
					}
					upAndDown = true;
					prevHeight = currentHeight;
					if (currentHeight > maxHeight) { maxHeight = currentHeight; }
				}

				// end of the line(return the tool back to starting position)
				if (k == 0)
				{
					mPathVertices << currentPathPointX << currentPathPointY + (size * (maxHeight - j)) << currentPathPointZ;
					mPathColors << 0.9844 << 0.7578 << 0.0117;

					mPathVertices << currentPathPointX << currentPathPointY + (size * (maxHeight - j)) << currentPathPointZ + (size*(zDimension));
					mPathColors << 0.9844 << 0.7578 << 0.0117;
				}
			}
		}
	}
}
