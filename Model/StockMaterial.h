#pragma once
#include "BoundingBox.h"
#include "Point3D.h"
#include "vector"
#include "qvector.h"
#include "qopengl.h"
using namespace std;

class StockMaterial
{
public:
	StockMaterial();
	~StockMaterial();

	BoundingBox StockMaterialGrid() const;
	double ConstituentSize() const;
    QVector<GLfloat>& GridVertices();
	QVector<GLfloat>& GridColors();

	//void setConstituentSize(double size);
	void findMinimaMaxima(const vector<Point3D>& lop);
	void processVertices(double size);

private:
	BoundingBox mGridBoundingBox;
	double mConstituentSize = 0; // Constituent refers to a cube shape
	QVector<GLfloat> mGridVertices;
	QVector<GLfloat> mGridColors;
};