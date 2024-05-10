#include "stdafx.h"
#include "Point3D.h"

Point3D::Point3D() {}
Point3D::Point3D(const float& inX, const float& inY, const float& inZ) :mx(inX), my(inY), mz(inZ) {}
Point3D::~Point3D() {}

void Point3D::setX(const float& inX) {mx = inX;}
void Point3D::setY(const float& inY) {my = inY;}
void Point3D::setZ(const float& inZ) {mz = inZ;}

const float& Point3D::X()  const{return mx;}
const float& Point3D::Y() const{return my;}
const float& Point3D::Z() const{return mz;}