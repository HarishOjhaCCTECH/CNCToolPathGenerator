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

    void stlVoxels(const vector<Triangle>& lot, const vector<Point3D>& lop);

    const QVector<GLfloat>& getGridVertices1() const;
    const QVector<GLfloat>& getGridVertices2() const;
    const QVector<GLfloat>& getGridVertices3() const;
    const QVector<GLfloat>& getColors() const;
    const vector<vector<vector<BoundingBox>>>& getBlocks() const;
    const QVector<GLfloat>& getSTLVertices() const;
    const int& getBoxLimitPerAxis() const;

private:
    QVector<GLfloat> mGridVertices1;
    QVector<GLfloat> mGridVertices2;
    QVector<GLfloat> mGridVertices3;
    QVector<GLfloat> colors;
    vector<vector<vector<BoundingBox>>> boxes;
    QVector<GLfloat> mSTLVertices;
    int boxLimitPerAxis;
};
