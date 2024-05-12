#include "stdafx.h"
#include "DataManager.h"

DataManager::DataManager(QMainWindow* parent)
{
	mGeneratedToolPath = new ToolPath();
	mStockMaterial = new Voxel();
	mToolCylinder = new ToolCylinder();
	mToolPathTxt = new ToolPathTxtWriter();
}
DataManager::~DataManager()
{
	delete mStockMaterial;
	delete mToolCylinder;
	delete mGeneratedToolPath;
}

const Voxel& DataManager::stockMaterial() {	return *mStockMaterial;}
const ToolCylinder& DataManager::toolCylinder() { return *mToolCylinder; }
const ToolPath& DataManager::generatedToolPath() { return *mGeneratedToolPath; }

void DataManager::setShapeFilePath(const char* inChar) { mShapeFilePath = inChar; }
void DataManager::setToolSize(const float& inFloat) { mToolSize = inFloat; }

void DataManager::processData()
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
		mToolStartPoint.setX(xStart);
		mToolStartPoint.setY(yStart);
		mToolStartPoint.setZ(zStart);
		mToolCylinder = new ToolCylinder(mToolSize/4, xStart, yStart, zStart);
		mStockMaterial->stlVoxels(lot, lop);	
		mGeneratedToolPath = new ToolPath(mStockMaterial->getBlocks(), Point3D(xStart, yStart, zStart));
	}
}

void DataManager::simulate()
{
	float p = 0;
	float q = 0;
	float r = mToolSize*(-1);

	float translateMatrix[4][4]{
		{1,0,0,p},
		{0,1,0,q},
		{0,0,1,r},
		{0,0,0,1}
	};

	float translateStartPoint[4][1]{
		{mToolCylinder->Center().X()},
		{mToolCylinder->Center().Y()},
		{mToolCylinder->Center().Z()},
		{1}
	};

	float finalPoint[4][1]{
		{0},
		{0},
		{0},
		{0}
	};
	for (int i = 0; i < 4; i++)
	{
		for (int k = 0; k < 4; k++)
		{
			finalPoint[i][0] += translateMatrix[i][k] * translateStartPoint[k][0];
		}
	}
	mToolCylinder = new ToolCylinder(mToolSize / 4, finalPoint[0][0], finalPoint[1][0], finalPoint[2][0]);




}

void DataManager::savefile()
{
	mToolPathTxt = new ToolPathTxtWriter();
	mToolPathTxt->generateFile(mGeneratedToolPath->ToolPathVertices());
}