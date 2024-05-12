#pragma once
#include "string"
#include "Triangle.h"
#include "Point3D.h"

using namespace std;

class STLReader
{
public:
	STLReader();
	~STLReader();

	void read(const string& stlFilePath, vector<Triangle>& lot, vector<Point3D>& lop);
	const float& largestModulusInteger() const;
	
private:
	float mLargestModulusInteger = 0;
};