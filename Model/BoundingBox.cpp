#include "stdafx.h"
#include "BoundingBox.h"

BoundingBox::BoundingBox() : minima(Point3D(0, 0, 0)), maxima(Point3D(0, 0, 0)), existence(false) {}
BoundingBox::BoundingBox(const Point3D& min, const Point3D& max, bool exists): minima(min), maxima(max), existence(exists) {}
BoundingBox::~BoundingBox() {}