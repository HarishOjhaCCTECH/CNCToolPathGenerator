#include "stdafx.h"
#include "DataStorage.h"

DataStorage::DataStorage(QMainWindow* parent) 
{
	QString currentPath = QCoreApplication::applicationDirPath();
	QDir dir(currentPath);
	dir.cdUp();
	dir.cdUp();
	QString parentPath = dir.path();
	QString stlFilePath = parentPath + "/Model/Cube.stl";
	stlReaderObj.read(stlFilePath.toStdString(), lot, lop);

	float distBetweenPoints = sqrt(pow(lop.at(0).X() - lop.at(1).X(), 2) + pow(lop.at(0).Y() - lop.at(1).Y(), 2) + pow(lop.at(0).Z() - lop.at(1).Z(), 2));
	int boxPerAxis = stlReaderObj.largestModulusInteger();
	mStockMaterial = new Voxel(boxPerAxis, distBetweenPoints);
	
	float xStart = mStockMaterial->getBlocks().at(boxPerAxis-1).at(boxPerAxis-1).at(boxPerAxis-1).maxima().X();
	float yStart = mStockMaterial->getBlocks().at(boxPerAxis-1).at(boxPerAxis-1).at(boxPerAxis-1).maxima().Y();
	float zStart = mStockMaterial->getBlocks().at(boxPerAxis-1).at(boxPerAxis-1).at(boxPerAxis-1).maxima().Z();
	mToolCylinder = new Cylinder(distBetweenPoints/4, xStart,yStart,zStart);

	mStockMaterial->stlVoxels(lot, lop);
	mGeneratedToolPath = new ToolPath(mStockMaterial->getBlocks());
}
DataStorage::~DataStorage() 
{
	delete mStockMaterial;
	delete mToolCylinder;
	delete mGeneratedToolPath;
}

const Voxel& DataStorage::stockMaterial() {	return *mStockMaterial;}
const Cylinder& DataStorage::toolCylinder() { return *mToolCylinder; }
const ToolPath& DataStorage::generatedToolPath() { return *mGeneratedToolPath; }