#include "stdafx.h"
#include "ToolCylinder.h"

ToolCylinder::ToolCylinder() {}

ToolCylinder::ToolCylinder(const GLfloat& drillRadius, float inCenX, float inCenY, float inCenZ)
{
	mPolesVertices.clear();
	mCenter.setX(inCenX);
	mCenter.setY(inCenY);
	mCenter.setZ(inCenZ);
	GLfloat cylinderHeight = 20;
	GLfloat cylinderRadius = drillRadius;
	GLfloat numOfCylinderPeriferryPoints = 360.f;
	for (int i = 0; i < numOfCylinderPeriferryPoints; ++i)
	{
		GLfloat u = i / (GLfloat)numOfCylinderPeriferryPoints;
		EachPole pole;
		pole.x = mCenter.X() + cylinderRadius * cos(2 * M_PI * u);
		pole.z = mCenter.Z() + cylinderRadius * sin(2 * M_PI * u);
		pole.yStart = mCenter.Y();
		pole.yEnd = pole.yStart+cylinderHeight;
		poles.push_back(pole);
	}
	for (int i = 0; i < numOfCylinderPeriferryPoints; i++)
	{
		mPolesVertices << poles[i].x << poles[i].yStart << poles[i].z;
		mPolesVertices << poles[i].x << poles[i].yEnd << poles[i].z;
		mPolesColors << 1 << 1 << 1;
		mPolesColors << 1 << 1 << 1;
	}
	
}

ToolCylinder::~ToolCylinder() {}

const Point3D& ToolCylinder::Center() { return mCenter; }
QVector<GLfloat> ToolCylinder::PoleVertices() const { return mPolesVertices; }
QVector<GLfloat> ToolCylinder::PolColors() const { return mPolesColors; }
