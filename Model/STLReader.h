// this .h file contains the declarations for class STLreader
// purpose of this class is to read the the stl files of 3d figures and store it in dtructred way to optimize the space
#pragma once
#include <vector>
#include <string>
#include "Point3D.h"
#include "Triangle.h"
class STLReader {
public:
    STLReader(); //default constructor
    ~STLReader(); // destructor
    //below function reads from the stl file and stores the points into "lop"(list ofpoints) and in "lot"(list of triangles)
    void read(std::string stlFilePath, std::vector<Triangle>& lot, std::vector<Point3D>& lop);
};