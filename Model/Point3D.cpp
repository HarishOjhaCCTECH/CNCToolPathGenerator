#include "stdafx.h"
#include "Point3D.h"

Point3D::Point3D(): mx(0),my(0),mz(0) {}
Point3D::Point3D(const double& inX, const double& inY, const double& inZ) :mx(inX), my(inY), mz(inZ) {}
Point3D::~Point3D() {}

void Point3D::setX(const double& inX) {mx = inX;}
void Point3D::setY(const double& inY) {my = inY;}
void Point3D::setZ(const double& inZ) {mz = inZ;}

const double& Point3D::X() const{return mx;}
const double& Point3D::Y() const{return my;}
const double& Point3D::Z() const{return mz;}

bool Point3D::operator<(const Point3D& other) const
{
    if (mx < other.mx)
        return true;
    else if (mx > other.mx)
        return false;
    else if (my < other.my)
        return true;
    else if (my > other.my)
        return false;
    else
        return mz < other.mz;
}
bool Point3D::operator>(const Point3D& other) const{return other < *this;}
bool Point3D::operator<=(const Point3D& other) const{return !(other < *this);}
bool Point3D::operator>=(const Point3D& other) const{return !(*this < other);}
