#include "stdafx.h"
#include "DataManager.h"

DataManager::DataManager() {}
DataManager::~DataManager() {}

void DataManager::processData(double size)
{
	// read stl
	QString stlFilePath= "C:/Users/Harish Ojha/Downloads/Cube.stl";
	stlReaderObj.read(stlFilePath.toStdString(), lot, lop);

	// find minima, maxima
	mStockMaterial.findMinimaMaxima(lop);

	// take tool size from user
	mStockMaterial.setConstituentSize(size);

	// making stl's voxel grid
	mStlVoxels.stlVoxelFinding(lot, lop, mStockMaterial);

	// making vertices vector for rendering stock material
	mStockMaterial.processVertices();
}

const  StockMaterial& DataManager::Stock() const { return mStockMaterial; }