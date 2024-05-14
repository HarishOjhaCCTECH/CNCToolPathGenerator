#include "stdafx.h"
#include "STLVoxel.h"
#include "StockMaterial.h"

STLVoxel::STLVoxel() {}
STLVoxel::~STLVoxel() {}
void STLVoxel::stlVoxelFinding(vector<Point3D>& lop, StockMaterial& stock)
{
	int xDimension = int(stock.StockMaterialGrid().Maxima().X() - stock.StockMaterialGrid().Minima().X()) + 1;
	int yDimension = int(stock.StockMaterialGrid().Maxima().Y() - stock.StockMaterialGrid().Minima().Y()) + 1;
	int zDimension = int(stock.StockMaterialGrid().Maxima().Z() - stock.StockMaterialGrid().Minima().Z()) + 1;
	mSTLGrid.resize(xDimension, vector<vector<bool>>(yDimension, vector<bool>(zDimension)));

	Point3D startPoint(stock.StockMaterialGrid().Minima().X(), stock.StockMaterialGrid().Minima().Y(), stock.StockMaterialGrid().Minima().Z());

	int len = stock.ConstituentSize();

	for (auto& p : lop)
	{
		float px = p.X();
		float py = p.Y();
		float pz = p.Z();

		// For every point, looping through the mSTLGrid
		for (int i = 0; i < xDimension; i++)
		{
			for (int j = 0; j < yDimension; j++)
			{
				for (int k = 0; k < zDimension; k++)
				{
					float x_min = startPoint.X() + (i * len);
					float x_max = x_min + (len);

					float y_min = startPoint.Y() + (j * len);
					float y_max = y_min + (len);

					float z_min = startPoint.Z() + (k * len);
					float z_max = z_min + (len);


					if ((px >= x_min && px <= x_max) && (py >= y_min && py <= y_max) && (pz >= z_min && pz <= z_max))
					{
						mSTLGrid[i][j][k] = true;
					}
				}
			}
		}
	}
}