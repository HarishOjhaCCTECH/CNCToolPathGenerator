#include "stdafx.h"
#include "DataManager.h"

DataManager::DataManager():mStockMaterial(new StockMaterial()), mStlVoxels(new VoxelGrid()), mPath(new ToolPath()), mTool(new ToolCylinder()), mWriter(new ToolPathTxtWriter()) {}
DataManager::~DataManager() {}

StockMaterial& DataManager::Stock() { return *mStockMaterial; }
VoxelGrid& DataManager::StlVoxels() { return *mStlVoxels; }
ToolPath& DataManager::Path() { return *mPath; }
ToolCylinder& DataManager::Tool() { return *mTool; }
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

	// find tool path
	mPath->findPath(mStlVoxels->STLGrid(), mStockMaterial->StockMaterialGrid(), size);
}

void DataManager::simulate(double size, int position)
{
	mTool = new ToolCylinder(size / 2, mPath->PathVertices().at(position), mPath->PathVertices().at(position + 1), mPath->PathVertices().at(position + 2));
}

void DataManager::saveFile() { mWriter->generateFile(mPath->PathVertices()); }