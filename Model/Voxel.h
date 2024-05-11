#pragma once
#include <vector>
#include <QVector>
#include "Point3D.h"
#include "BoundingBox.h"
#include "Triangle.h"
using namespace std;
class Voxel
{
public:
    Voxel();
    Voxel(float largeModulusInteger, float distBetweenPoints);
    ~Voxel();

    const QVector<GLfloat>& getGridVertices1();
    const QVector<GLfloat>& getGridVertices2();
    const QVector<GLfloat>& getGridVertices3();
    const QVector<GLfloat>& getColors();
    const vector<vector<vector<BoundingBox>>>& getBlocks();
    void stlVoxels(const vector<Triangle>& lot, const vector<Point3D>& lop);

    const QVector<GLfloat>& getSTLVertices1();
    const QVector<GLfloat>& getSTLVertices2();
    const QVector<GLfloat>& getSTLVertices3();

    const int& getBoxLimitPerAxis();

private:
    QVector<GLfloat> mGridVertices1;
    QVector<GLfloat> mGridVertices2;
    QVector<GLfloat> mGridVertices3;
    QVector<GLfloat> colors;
    //float startPoint[3] = { -10,-10,-10 };
    vector<vector<vector<BoundingBox>>> boxes;

    QVector<GLfloat> mSTLVertices1;
    QVector<GLfloat> mSTLVertices2;
    QVector<GLfloat> mSTLVertices3;

    int boxLimitPerAxis;

};
