#pragma once
#include <gl/GL.h>
#include <EachPole.h>

class Cylinder
{
public:
	Cylinder();
	Cylinder(const GLfloat& drillRadius);
	~Cylinder();
	
	const QVector<EachPole>& getPoles();

private:
	QVector<EachPole> poles;
};