#pragma once
#include "Point3D.h"
class BoundingBox
{
public:
	BoundingBox();
	BoundingBox(const Point3D& min, const Point3D& max, bool exists);
	~BoundingBox();

	Point3D minima;
	Point3D maxima;
	bool existence;

};