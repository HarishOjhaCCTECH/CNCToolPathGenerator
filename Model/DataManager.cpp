#include "stdafx.h"
#include "DataManager.h"

DataManager::DataManager() {}
DataManager::~DataManager() {}

void DataManager::processData(double size, string filePath)
{
	// read stl
	stlReader.readSTL(filePath, triangulation);

	// find minima, maxima
	mStockMaterial.findMinimaMaxima(triangulation.uniquePoints());

	// take tool size from user
	mStockMaterial.setConstituentSize(size);

	// making stl's voxel grid
	mStlVoxels.stlVoxelFinding(triangulation.uniquePoints(), mStockMaterial);

	// making vertices vector for rendering stock material
	mStockMaterial.processVertices();
}

const  StockMaterial& DataManager::Stock() const { return mStockMaterial; }