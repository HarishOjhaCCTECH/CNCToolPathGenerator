#include "stdafx.h"
#include "DataManager.h"

DataManager::DataManager():mStockMaterial(new StockMaterial()), mStlVoxels(new VoxelGrid()) {}
DataManager::~DataManager() {}

StockMaterial& DataManager::Stock() { return *mStockMaterial; }
VoxelGrid& DataManager::StlVoxels() { return *mStlVoxels; }

void DataManager::processData(double size, string filePath)
{
	// read stl
	stlReader.read(filePath, triangulation.listOfTriangles(), triangulation.listOfPoints());

	// find minima, maxima
	mStockMaterial->findMinimaMaxima(triangulation.listOfPoints());

	// take tool size from user find the vertices of every cube
	mStockMaterial->processVertices(size);

	// making stl's voxel grid
	mStlVoxels->stlVoxelFinding(triangulation.listOfPoints(), mStockMaterial->StockMaterialGrid(), mStockMaterial->ConstituentSize());
}
