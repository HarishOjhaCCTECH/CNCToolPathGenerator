#include "stdafx.h"
#include "DataStorage.h"

DataStorage::DataStorage(QMainWindow* parent) 
{
	
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

void DataStorage::setShapeFilePath(const char* inChar) { mShapeFilePath = inChar; }
void DataStorage::setToolSize(const float& inFloat) { mToolSize = inFloat; }

void DataStorage::processData()
{
	QString currentPath = QCoreApplication::applicationDirPath();
	QDir dir(currentPath);
	dir.cdUp();
	dir.cdUp();
	QString parentPath = dir.path();
	QString stlFilePath = parentPath + mShapeFilePath;

	stlReaderObj.read(stlFilePath.toStdString(), lot, lop);
	float distBetweenPoints = 0;
	int boxPerAxis = 0;
	float xStart = 0;
	float yStart = 0;
	float zStart = 0;
	if (lot.size() != 0)
	{
		distBetweenPoints = sqrt(pow(lop.at(0).X() - lop.at(1).X(), 2) + pow(lop.at(0).Y() - lop.at(1).Y(), 2) + pow(lop.at(0).Z() - lop.at(1).Z(), 2));
		boxPerAxis = stlReaderObj.largestModulusInteger();

		mStockMaterial = new Voxel(boxPerAxis, mToolSize);
		

		xStart = (mStockMaterial->getBlocks().at(boxPerAxis - 1).at(boxPerAxis - 1).at(boxPerAxis - 1).maxima().X() + mStockMaterial->getBlocks().at(boxPerAxis - 1).at(boxPerAxis - 1).at(boxPerAxis - 1).minima().X())/2;
		yStart = (mStockMaterial->getBlocks().at(boxPerAxis - 1).at(boxPerAxis - 1).at(boxPerAxis - 1).maxima().Y() + mStockMaterial->getBlocks().at(boxPerAxis - 1).at(boxPerAxis - 1).at(boxPerAxis - 1).minima().Y())/2;
		zStart = mToolSize+((mStockMaterial->getBlocks().at(boxPerAxis - 1).at(boxPerAxis - 1).at(boxPerAxis - 1).maxima().Z() + mStockMaterial->getBlocks().at(boxPerAxis - 1).at(boxPerAxis - 1).at(boxPerAxis - 1).minima().Z())/2);
		mToolCylinder = new Cylinder(mToolSize/4, xStart, yStart, zStart);

		mStockMaterial->stlVoxels(lot, lop);
		
		mGeneratedToolPath = new ToolPath(mStockMaterial->getBlocks(), Point3D(xStart, yStart, zStart));
	}



}