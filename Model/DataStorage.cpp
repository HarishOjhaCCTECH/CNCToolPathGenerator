#include "stdafx.h"
#include "DataStorage.h"
DataStorage::DataStorage() 
{
	stlReaderObj.read("Cube.stl", lot, lop);
	stockMaterial = new Voxel(.5, .5, .5);
	controller.dataPass(*stockMaterial);
	drillTool = new Cylinder(0.25);

}
DataStorage::~DataStorage() 
{
	delete stockMaterial;
	delete drillTool;
}