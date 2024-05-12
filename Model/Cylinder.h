#pragma once
#include <gl/GL.h>
#include "Point3D.h"

class EachPole {
public:
	GLfloat x;
	GLfloat z;
	GLfloat yStart;
	GLfloat yEnd;
};

class Cylinder
{
public:
	Cylinder();
	Cylinder(const GLfloat& drillRadius, float inCenX, float inCenY, float inCenZ);
	~Cylinder();
	
	const QVector<GLfloat> getPoleVertices() const;

private:
	QVector<EachPole> poles;
	QVector<GLfloat> mPolesVertices;
	Point3D mCenter;
};