#include "stdafx.h"
#include "DataStorage.h"
DataStorage::DataStorage(QMainWindow* parent) 
{
	stlReaderObj.read("Cube.stl", lot, lop);
	stockMaterial = new Voxel(.5, .5, .5);
	drillTool = new Cylinder(0.25);

}
DataStorage::~DataStorage() 
{
	delete stockMaterial;
	delete drillTool;
}