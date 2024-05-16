#include "stdafx.h"
#include "Triangle.h"

Triangle::Triangle():mv1(0), mv2(0), mv3(0){}
Triangle::Triangle(int v1, int v2, int v3) :mv1(v1), mv2(v2), mv3(v3) {}
Triangle::~Triangle() {}

int Triangle::v1()const { return mv1; }
int Triangle::v2()const { return mv2; }
int Triangle::v3()const { return mv3; }