#include "stdafx.h"
#include "BoundingBox.h"

BoundingBox::BoundingBox() : mMinima(Point3D(0, 0, 0)), mMaxima(Point3D(0, 0, 0)), mExistence(false) {}
BoundingBox::BoundingBox(const Point3D& min, const Point3D& max, bool exists): mMinima(min), mMaxima(max), mExistence(exists) {}
BoundingBox::~BoundingBox() {}

const Point3D& BoundingBox::Minima()  const { return mMinima; }
const Point3D& BoundingBox::Maxima()  const { return mMaxima; }
const bool& BoundingBox::existence()  const { return mExistence; }

void BoundingBox::setMinima(const Point3D& inPoint) {
	mMinima.setX(inPoint.X());
	mMinima.setY(inPoint.Y());
	mMinima.setZ(inPoint.Z());
}

void BoundingBox::setMaxima(const Point3D& inPoint) {
	mMaxima.setX(inPoint.X());
	mMaxima.setY(inPoint.Y());
	mMaxima.setZ(inPoint.Z());
}

void BoundingBox::setExistence(const bool& inBool){	mExistence = inBool;}