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
	stockMaterial = new Voxel(stlReaderObj.largestModulusInteger, distBetweenPoints);
	drillTool = new Cylinder(0.25);
	stockMaterial->stlVoxels(lot, lop);
	
	int k = 0;
}
DataStorage::~DataStorage() 
{
	delete stockMaterial;
	delete drillTool;
}