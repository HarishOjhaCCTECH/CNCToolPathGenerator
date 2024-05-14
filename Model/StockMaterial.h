#pragma once
#include "BoundingBox.h"
#include "Point3D.h"
#include "StockMaterial.h"
using namespace std;

class StockMaterial
{
public:
	StockMaterial();
	~StockMaterial();

	const BoundingBox StockMaterialGrid() const;
	const double ConstituentSize() const;
	const QVector<GLfloat> GridVertices() const;

	void setConstituentSize(double size);
	void findMinimaMaxima(const vector<Point3D>& lop);
	void processVertices();

private:
	BoundingBox mGridBoundingBox;
	double mConstituentSize = 0; // Constituent refers to a cube shape
	QVector<GLfloat> mGridVertices;
};