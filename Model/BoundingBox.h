#pragma once
#include "Point3D.h"

class BoundingBox
{
public:
	BoundingBox();
	BoundingBox(const Point3D& min, const Point3D& max, bool exists);
	~BoundingBox();

	const Point3D& Minima() const;
	const Point3D& Maxima() const;

	void setMinima(const Point3D& inPoint);
	void setMaxima(const Point3D& inPoint);

private:
	Point3D mMinima;
	Point3D mMaxima;
};