#pragma once

class Point3D
{
public:
	Point3D();
	Point3D(const double& inX, const double& inY, const double& inZ);
	~Point3D();

	void setX(const double& inX);
	void setY(const double& inY);
	void setZ(const double& inZ);

	const double& X() const;
	const double& Y() const;
	const double& Z() const;

    bool operator<(const Point3D& other) const;
    bool operator>(const Point3D& other) const;
    bool operator<=(const Point3D& other) const;
	bool operator>=(const Point3D& other) const;

private:
	double mx;
	double my;
	double mz;
};