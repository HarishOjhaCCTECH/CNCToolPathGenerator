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

class ToolCylinder
{
public:
	ToolCylinder();
	ToolCylinder(const GLfloat& drillRadius, float inCenX, float inCenY, float inCenZ);
	~ToolCylinder();
	
	const Point3D& Center();
	QVector<GLfloat> PoleVertices() const;
	QVector<GLfloat> PolColors() const;

private:
	QVector<EachPole> poles;
	QVector<GLfloat> mPolesVertices;
	QVector<GLfloat> mPolesColors;
	Point3D mCenter;
};