#pragma once
#include <vector>
#include <QVector>
#include "Point3D.h"
#include "BoundingBox.h"
using namespace std;
class Voxel
{
public:
    Voxel();
    Voxel(float xLen, float yLen, float zLen);
    ~Voxel();

    const QVector<GLfloat>& getVertices1();
    const QVector<GLfloat>& getVertices2();
    const QVector<GLfloat>& getVertices3();
    const QVector<GLfloat>& getColors();
    const vector<vector<vector<BoundingBox>>>& getBlocks();

private:
    QVector<GLfloat> mvertices1;
    QVector<GLfloat> mvertices2;
    QVector<GLfloat> mvertices3;
    QVector<GLfloat> colors;
    float startPoint[3] = { 1,1,1 };
    vector<vector<vector<BoundingBox>>> boxes;
};
