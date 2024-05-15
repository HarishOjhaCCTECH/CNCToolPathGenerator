#pragma once
class Point3D
{
public:
    Point3D();
    Point3D(double x, double y, double z);
    ~Point3D();
    double X() const;
    double Y() const;
    double Z() const;

    void setX(double inX);
    void setY(double inY);
    void setZ(double inZ);
    bool operator<(const Point3D& other) const;
private:
    double mX;
    double mY;
    double mZ;
};