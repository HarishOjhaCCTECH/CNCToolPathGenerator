#include "stdafx.h"
#include "DataManager.h"

DataManager::DataManager():mStockMaterial(new StockMaterial()), mStlVoxels(new VoxelGrid()) {}
DataManager::~DataManager() {}

void DataManager::processData(double size, string filePath)
{
	// read stl
	stlReader.read(filePath, triangulation.listOfTriangles(), triangulation.listOfPoints());

	// find minima, maxima
	mStockMaterial->findMinimaMaxima(triangulation.listOfPoints());

	// take tool size from user
	mStockMaterial->processVertices(size);

	// making stl's voxel grid
	mStlVoxels->stlVoxelFinding(triangulation.listOfPoints(), mStockMaterial->StockMaterialGrid(), mStockMaterial->ConstituentSize());

	// making vertices vector for rendering stock material
	
}

StockMaterial& DataManager::Stock(){ return *mStockMaterial; }
VoxelGrid& DataManager::StlVoxels() { return *mStlVoxels; }