#include "stdafx.h"
#include "Point3D.h"

Point3D::Point3D() : mX(0), mY(0), mZ(0) {}

Point3D::Point3D(double x, double y, double z) : mX(x), mY(y), mZ(z) {}

Point3D::~Point3D() {}

double Point3D::X() const { return mX; }
double Point3D::Y() const {return mY;}
double Point3D::Z() const {return mZ;}

bool Point3D::operator<(const Point3D& other) const
{
    if (mX < other.mX)
        return true;
    if (mX > other.mX)
        return false;

    if (mY < other.mY)
        return true;
    if (mY > other.mY)
        return false;

    return mZ < other.mZ;
}


void Point3D::setX(double inX) { mX = inX; }
void Point3D::setY(double inY) { mY = inY; }
void Point3D::setZ(double inZ) { mZ = inZ; }