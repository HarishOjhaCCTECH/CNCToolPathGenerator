#include "stdafx.h"
#include "DataStorage.h"
DataStorage::DataStorage(QMainWindow* parent) 
{
	QString currentPath = QCoreApplication::applicationDirPath(); // Assuming Qt application

	// Navigate one directory up
	QDir dir(currentPath);
	dir.cdUp();
	dir.cdUp();
	QString parentPath = dir.path();

	// Construct the relative path to the STL file
	QString stlFilePath = parentPath + "/Model/Cube.stl";

	// Read the STL file using the relative path
	stlReaderObj.read(stlFilePath.toStdString(), lot, lop);
	float distBetweenPoints = sqrt(pow(lop.at(0).X() - lop.at(1).X(), 2) + pow(lop.at(0).Y() - lop.at(1).Y(), 2) + pow(lop.at(0).Z() - lop.at(1).Z(), 2));
	int boxPerAxis = stlReaderObj.largestModulusInteger;
	stockMaterial = new Voxel(boxPerAxis, distBetweenPoints);
	float xStart = stockMaterial->getBlocks().at(boxPerAxis-1).at(boxPerAxis-1).at(boxPerAxis-1).maxima.X();
	float yStart = stockMaterial->getBlocks().at(boxPerAxis-1).at(boxPerAxis-1).at(boxPerAxis-1).maxima.Y();
	float zStart = stockMaterial->getBlocks().at(boxPerAxis-1).at(boxPerAxis-1).at(boxPerAxis-1).maxima.Z();
	
	toolCylinder = new Cylinder(distBetweenPoints/4, xStart,yStart,zStart);
	stockMaterial->stlVoxels(lot, lop);
	
	generatedToolPath = new ToolPath(stockMaterial->getBlocks());
	int k = 0;
}
DataStorage::~DataStorage() 
{
	delete stockMaterial;
	delete toolCylinder;
}