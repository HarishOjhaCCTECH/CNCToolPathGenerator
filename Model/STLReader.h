#pragma once

#include <map>
#include <string>
#include <vector>
#include "Triangulation.h"
class STLReader
{
public:
    // Function to read data from an STL file and populate a Triangulation object
    STLReader();
    ~STLReader();
    void readSTL(std::string& filePath, Triangulation& triangulation);
};