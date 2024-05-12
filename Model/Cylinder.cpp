#include "stdafx.h"
#include "Cylinder.h"

Cylinder::Cylinder() {}

Cylinder::Cylinder(const GLfloat& drillRadius, float inCenX, float inCenY, float inCenZ) 
{
	mCenter.setX(inCenX);
	mCenter.setY(inCenY);
	mCenter.setZ(inCenZ);
	GLfloat cylinderHeight = drillRadius*2;
	GLfloat cylinderRadius = drillRadius;
	GLfloat numOfCylinderPeriferryPoints = 360.f;
	for (int i = 0; i < numOfCylinderPeriferryPoints; ++i)
	{
		GLfloat u = i / (GLfloat)numOfCylinderPeriferryPoints;
		EachPole pole;
		pole.x = mCenter.X() + cylinderRadius * cos(2 * M_PI * u);
		pole.z = mCenter.Z() + cylinderRadius * sin(2 * M_PI * u);
		pole.yStart = mCenter.Y();
		pole.yEnd = cylinderHeight;
		poles.push_back(pole);
	}
	for (int i = 0; i < numOfCylinderPeriferryPoints; i++)
	{
		mPolesVertices << poles[i].x << poles[i].yStart << poles[i].z;
		mPolesVertices << poles[i].x << poles[i].yEnd << poles[i].z;
	}
	
}

Cylinder::~Cylinder() {}

const QVector<GLfloat> Cylinder::getPoleVertices() const { return mPolesVertices; }
