#include "stdafx.h"
#include "Triangle.h"

Triangle::Triangle():mv1(0),mv2(0),mv3(0) {}
Triangle::Triangle(const int inV1, const int inV2, const int inV3) :mv1(inV1), mv2(inV2), mv3(inV3) {}
Triangle::~Triangle() {}

int Triangle::v1()const { return mv1; }
int Triangle::v2()const { return mv2; }
int Triangle::v3()const { return mv3; }