#pragma once
#include "string"
#include "ToolPath.h"
#include "fstream"

using namespace std;

class ToolPathTxtWriter
{
public:
	ToolPathTxtWriter();
	~ToolPathTxtWriter();
	void generateFile(const QVector<GLfloat>& pathData);
};