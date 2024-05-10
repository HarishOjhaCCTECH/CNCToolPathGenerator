#pragma once

class Point3D
{
public:
	Point3D();
	Point3D(const float& inX, const float& inY, const float& inZ);
	~Point3D();

	void setX(const float& inX);
	void setY(const float& inY);
	void setZ(const float& inZ);

	const float& X() const;
	const float& Y() const;
	const float& Z() const;

private:
	float mx;
	float my;
	float mz;
};