#pragma once
#include <vector>
#include <string>
#include "Point3D.h"
#include "Triangle.h"
using namespace std;

class STLReader
{
public:
    STLReader();
    ~STLReader();
    void read(std::string stlFilePath, std::vector<Triangle>& lot, std::vector<Point3D>& lop);
};