#pragma once
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include "Voxel.h"
#include "Cylinder.h"
#include "ToolPath.h"

using namespace std;
class QOpenGLTexture;
class QOpenGLShader;
class QOpenGLShaderProgram;
class QOpenGLPaintDevice;

class OpenGLWindow : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

public:
    OpenGLWindow(const QColor& background, QMainWindow* parent);
    ~OpenGLWindow();
    void setRenderingAttributes(Voxel& stockMaterial, Cylinder& toolCylinder, ToolPath& generatedToolPath);

protected:
    void paintGL() override;
    void initializeGL() override;

private:
    void reset();
    void mouseMoveEvent(QMouseEvent* event);
    void wheelEvent(QWheelEvent* event);
    void zoomIn();
    void zoomOut();

private:
    bool mAnimating = false;
    QOpenGLContext* mContext = nullptr;
    QOpenGLPaintDevice* mDevice = nullptr;

    QOpenGLShader* mVshader = nullptr;
    QOpenGLShader* mFshader = nullptr;
    QOpenGLShaderProgram* mProgram = nullptr;

    QList<QVector3D> mNormals;
    QOpenGLBuffer mVbo;

    QColor mBackground;
    QMetaObject::Connection mContextWatchConnection;

    GLint m_posAttr = 0;
    GLint m_colAttr = 0;
    GLint m_normAttr = 0;

    GLint m_matrixUniform = 0;

    GLint m_projectionMatrixUniform = 0;
    GLint m_viewMatrixUniform = 0;
    GLint m_modelMatrixUniform = 0;
    GLint m_normalMatrixUniform = 0;
    GLint m_lightPosUniform = 0;

    QQuaternion rotationAngle;
    QPoint lastPos;
    float scaleFactor = 5;
    
    QVector<GLfloat> mGridVerticesFront;
    QVector<GLfloat> mGridColors;
    QVector<GLfloat> mGridVerticesBack;
    QVector<GLfloat> mGridVerticesSide;

    
    QVector<GLfloat> mSTLGridColors;

    int boxLimitPerAxisRender = 0;

    QVector<GLfloat> mSTLVertices;
    QVector<GLfloat> mCylPoleVertices;
    QVector<GLfloat> mToolPathVertices;
};
