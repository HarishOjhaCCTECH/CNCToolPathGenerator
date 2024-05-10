#include "stdafx.h"
#include "Cylinder.h"

Cylinder::Cylinder() 
{	
	GLfloat cylinderHeight = 1.0f;
	GLfloat cylinderRadius = 0.5f;
	GLfloat numOfCylinderPeriferryPoints = 360.f;

	for (int i = 0; i < numOfCylinderPeriferryPoints; ++i)
	{
		GLfloat u = i / (GLfloat)numOfCylinderPeriferryPoints;
		EachPole pole;
		pole.x = 4 + cylinderRadius * cos(2 * M_PI * u);
		pole.z = -5 + cylinderRadius * sin(2 * M_PI * u);
		pole.yStart = 0.0f;
		pole.yEnd = cylinderHeight;
		poles.push_back(pole);
	}
}

Cylinder::Cylinder(const GLfloat& drillRadius) 
{
	GLfloat cylinderHeight = 1.0f;
	GLfloat cylinderRadius = drillRadius;
	GLfloat numOfCylinderPeriferryPoints = 360.f;
	for (int i = 0; i < numOfCylinderPeriferryPoints; ++i)
	{
		GLfloat u = i / (GLfloat)numOfCylinderPeriferryPoints;
		EachPole pole;
		pole.x = 4 + cylinderRadius * cos(2 * M_PI * u);
		pole.z = -5 + cylinderRadius * sin(2 * M_PI * u);
		pole.yStart = 0.0f;
		pole.yEnd = cylinderHeight;
		poles.push_back(pole);
	}
}

Cylinder::~Cylinder() {}

const QVector<EachPole>& Cylinder::getPoles()
{
	return poles;
}