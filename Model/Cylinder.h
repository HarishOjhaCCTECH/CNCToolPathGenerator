#pragma once
#include <gl/GL.h>
#include <EachPole.h>
#include "Point3D.h"

class Cylinder
{
public:
	Cylinder();
	Cylinder(const GLfloat& drillRadius, float inCenX, float inCenY, float inCenZ);
	~Cylinder();
	
	const QVector<GLfloat> getPoleVertices();

private:
	QVector<EachPole> poles;
	QVector<GLfloat> mPolesVertices;
	Point3D mCenter;
};