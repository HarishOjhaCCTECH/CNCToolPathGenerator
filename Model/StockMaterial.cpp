#include "stdafx.h"
#include "StockMaterial.h"

StockMaterial::StockMaterial() {}
StockMaterial::~StockMaterial() {}

BoundingBox StockMaterial::StockMaterialGrid() const { return mGridBoundingBox; }
double StockMaterial::ConstituentSize() const { return mConstituentSize; }
QVector<GLfloat>& StockMaterial::GridColors() { return mGridColors; }
QVector<GLfloat>& StockMaterial::GridVertices() { return mGridVertices; }

void StockMaterial::findMinimaMaxima(const vector<Point3D>& lop)
{
	double xMin = DBL_MAX;
	double yMin = DBL_MAX;
	double zMin = DBL_MAX;
	double xMax = DBL_MIN;
	double yMax = DBL_MIN;
	double zMax = DBL_MIN;

	for (int i = 0; i < lop.size(); i++)
	{
		//searching minima
		if (lop.at(i).X() < xMin) { xMin = lop.at(i).X(); }
		if (lop.at(i).Y() < yMin) { yMin = lop.at(i).Y(); }
		if (lop.at(i).Z() < zMin) { zMin = lop.at(i).Z(); }

		//searching maxima
		if (lop.at(i).X() > xMax) { xMax = lop.at(i).X(); }
		if (lop.at(i).Y() > yMax) { yMax = lop.at(i).Y(); }
		if (lop.at(i).Z() > zMax) { zMax = lop.at(i).Z(); }
	}
	mGridBoundingBox.setMaxima(Point3D(xMax, yMax, zMax));
	mGridBoundingBox.setMinima(Point3D(xMin, yMin, zMin));
}


void StockMaterial::processVertices(double size)
{
	mConstituentSize = size;
	int xDimension = int((mGridBoundingBox.Maxima().X() - mGridBoundingBox.Minima().X()) / size) + 1;
	int yDimension = int((mGridBoundingBox.Maxima().Y() - mGridBoundingBox.Minima().Y()) / size) + 2;
	int zDimension = int((mGridBoundingBox.Maxima().Z() - mGridBoundingBox.Minima().Z()) / size) + 2;

	Point3D stockStartPoint(mGridBoundingBox.Minima().X(), mGridBoundingBox.Minima().Y(), mGridBoundingBox.Minima().Z());

	// making vector for rendering stock material
	for (int i = 0; i < xDimension; i++)
	{
		for (int j = 0; j < yDimension; j++)
		{
			for (int k = 0; k < zDimension; k++)
			{
				float x_min = stockStartPoint.X() + (i * mConstituentSize);
				float x_max = x_min + (mConstituentSize);

				float y_min = stockStartPoint.Y() + (j * mConstituentSize);
				float y_max = y_min + (mConstituentSize);

				float z_min = stockStartPoint.Z() + (k * mConstituentSize);
				float z_max = z_min + (mConstituentSize);

				// front face
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
					mGridColors << 0.0117 << 0.8086 << 0.9844;
				}
			}
		}
	}
}

