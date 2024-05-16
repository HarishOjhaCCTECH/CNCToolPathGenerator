#include "stdafx.h"
#include "ToolPathTxtWriter.h"

ToolPathTxtWriter::ToolPathTxtWriter() {}
ToolPathTxtWriter::~ToolPathTxtWriter() {}

void ToolPathTxtWriter::generateFile(const QVector<GLfloat>& pathData)
{
	string fileData = "";
	for (int i = 0; i < pathData.size()/3; i++)
	{
		string tempStr = to_string(pathData.at(i)) + " " + to_string(pathData.at(i + 1)) + " " + to_string(pathData.at(i + 2)) + "\n";
		fileData += tempStr;
	}
	ofstream outputFile;
	outputFile.open("D:/GeneratedToolPath.txt");
	if (outputFile.is_open()) {
		outputFile << fileData;
		outputFile.close();
	}
}