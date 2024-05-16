#include "stdafx.h"
#include "OpenGLWindow.h"
#include <QOpenGLContext>
#include <QOpenGLPaintDevice>
#include <QOpenGLShaderProgram>
#include <QPainter>
#include <iostream>
#include <qopenglvertexarrayobject.h>

OpenGLWindow::OpenGLWindow(const QColor& background, QMainWindow* parent) :
	mBackground(background)
{
	setParent(parent);
	setMinimumSize(300, 250);
}
OpenGLWindow::~OpenGLWindow()
{
	reset();
}

void OpenGLWindow::reset()
{
	makeCurrent();
	mVbo.destroy();
	doneCurrent();
	QObject::disconnect(mContextWatchConnection);
}

void OpenGLWindow::paintGL()
{
	glClearColor(0.92f, 0.53f, 0.92f, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	mProgram->bind();
	glLineWidth(2.5f);

	QMatrix4x4 modelMatrix;
	QMatrix4x4 translationMatrix;
	QMatrix4x4 scaleMatrix;
	QMatrix4x4 rotationMatrix;
	QMatrix4x4 rotationMatrix1;
	QMatrix4x4 rotationMatrix2;
	QMatrix4x4 viewMatrix;
	QMatrix4x4 projectionMatrix;
	QMatrix3x3 normalMatrix;
	QVector3D lightPos;

	lightPos = QVector3D(0.0f, 0.0f, 20.0f);
	projectionMatrix.ortho(-100.0f * scaleFactor, 100.0f * scaleFactor, -100.0f * scaleFactor, 100.0f * scaleFactor, 0.00000000001f, 1000000.0f);

	translationMatrix.translate(0, 200, -400);
	scaleMatrix.scale(30.0);
	rotationMatrix1.rotate(rotationAngle);
	rotationMatrix2.rotate(180.0, 0.0, 1.0, 0.0);
	rotationMatrix = rotationMatrix1 * rotationMatrix2;

	modelMatrix = translationMatrix * scaleMatrix * rotationMatrix;
	viewMatrix.setToIdentity();
	normalMatrix = (modelMatrix.normalMatrix()).transposed();
	normalMatrix = (modelMatrix.normalMatrix());

	mProgram->setUniformValue(m_modelMatrixUniform, modelMatrix);
	mProgram->setUniformValue(m_viewMatrixUniform, viewMatrix);
	mProgram->setUniformValue(m_projectionMatrixUniform, projectionMatrix);
	mProgram->setUniformValue(m_normalMatrixUniform, normalMatrix);
	mProgram->setUniformValue(m_lightPosUniform, lightPos);

	glEnableVertexAttribArray(m_posAttr);
	glEnableVertexAttribArray(m_colAttr);

	// render Stock material
	if (mShowStockMaterial)
	{
		glVertexAttribPointer(m_posAttr, 3, GL_FLOAT, GL_FALSE, 0, mStockMaterialVertices.data());
		glVertexAttribPointer(m_colAttr, 3, GL_FLOAT, GL_FALSE, 0, mStockMaterialColors.data());
		glDrawArrays(GL_POLYGON, 0, mStockMaterialVertices.size() / 3);

	}

	// render stl shape
	if (mShowSTL)
	{
		glVertexAttribPointer(m_posAttr, 3, GL_FLOAT, GL_FALSE, 0, mSTLShapeVertices.data());
		glVertexAttribPointer(m_colAttr, 3, GL_FLOAT, GL_FALSE, 0, mSTLShapeColors.data());
		glDrawArrays(GL_POLYGON, 0, mSTLShapeVertices.size() / 3);

	}

	// rendering tool path
	if (mShowToolPath)
	{
		glVertexAttribPointer(m_posAttr, 3, GL_FLOAT, GL_FALSE, 0, mPathVers.data());
		glVertexAttribPointer(m_colAttr, 3, GL_FLOAT, GL_FALSE, 0, mPathColrs.data());
		glDrawArrays(GL_LINE_STRIP, 0, mPathVers.size() / 3);

	}

	// rendering tool
	if (mShowToolCylinder) {
		glVertexAttribPointer(m_posAttr, 3, GL_FLOAT, GL_FALSE, 0, mToolPoles.data());
		glVertexAttribPointer(m_colAttr, 3, GL_FLOAT, GL_FALSE, 0, mToolPoleColors.data());
		glDrawArrays(GL_LINES, 0, mToolPoles.size() / 3);

	}

	//rendering x-axis
	
	QVector<GLfloat> axisVertices;
	QVector<GLfloat> axisColors;
	axisVertices << 0 << 0 << 0;
	axisVertices << 80 << 0 << 0;
	axisColors << 1 << 0 << 0;
	axisColors << 1 << 0 << 0;
	glVertexAttribPointer(m_posAttr, 3, GL_FLOAT, GL_FALSE, 0, axisVertices.data());
	glVertexAttribPointer(m_colAttr, 3, GL_FLOAT, GL_FALSE, 0, axisColors.data());
	glDrawArrays(GL_LINES, 0, axisVertices.size() / 3);
	axisVertices.clear();
	axisColors.clear();

	// rendering y-axis
	axisVertices << 0 << 0 << 0;
	axisVertices << 0 << 80 << 0;
	axisColors << 0 << 1 << 0;
	axisColors << 0 << 1 << 0;
	glVertexAttribPointer(m_posAttr, 3, GL_FLOAT, GL_FALSE, 0, axisVertices.data());
	glVertexAttribPointer(m_colAttr, 3, GL_FLOAT, GL_FALSE, 0, axisColors.data());
	glDrawArrays(GL_LINES, 0, axisVertices.size() / 3);
	axisVertices.clear();
	axisColors.clear();

	//rendering z-axis
	axisVertices << 0 << 0 << 0;
	axisVertices << 0 << 0 << 80;
	axisColors << 0 << 0 << 1;
	axisColors << 0 << 0 << 1;
	glVertexAttribPointer(m_posAttr, 3, GL_FLOAT, GL_FALSE, 0, axisVertices.data());
	glVertexAttribPointer(m_colAttr, 3, GL_FLOAT, GL_FALSE, 0, axisColors.data());
	glDrawArrays(GL_LINES, 0, axisVertices.size() / 3);
	axisVertices.clear();
	axisColors.clear();
	

	glDisableVertexAttribArray(m_colAttr);
	glDisableVertexAttribArray(m_posAttr);
}


void OpenGLWindow::initializeGL()
{
	static const char* vertexShaderSource =
		"attribute highp vec4 posAttr; \n"
		"attribute lowp vec4 colAttr;\n"
		"attribute lowp vec3 norAttr;\n"
		"varying lowp vec4 col;\n"
		"varying vec3 vert;\n"
		"varying vec3 vertNormal;\n"
		"uniform highp mat4 projMatrix;\n"
		"uniform highp mat4 viewMatrix;\n"
		"uniform highp mat4 modelMatrix;\n"
		"uniform mat3 normalMatrix;\n"
		"void main() {\n"
		"   col = colAttr;\n"
		"   vert = posAttr.xyz;\n"
		"   gl_PointSize = 10.0;\n"
		"   vertNormal = normalMatrix * norAttr;\n"
		"   gl_Position = projMatrix * viewMatrix * modelMatrix * posAttr;\n"
		"}\n";

	static const char* fragmentShaderSource =
		"varying lowp vec4 col;\n"
		"varying highp vec3 vert;\n"
		"varying highp vec3 vertNormal;\n"
		"uniform highp vec3 lightPos;\n"
		"void main() {\n"
		"  highp vec3 L = normalize(lightPos - vert);\n"
		"   highp float NL = max(dot(normalize(vertNormal), L), 0.0);\n"
		"   highp vec3 color = vec3(col);\n"
		"   highp vec3 col1 = clamp(color * 0.2 + color * 0.8 * NL, 0.0, 1.0);\n"
		"   gl_FragColor = vec4(col1, 1.0);\n"
		"}\n";

	rotationAngle = QQuaternion::fromAxisAndAngle(180.0f, 0.0f, 1.0f, 0.0f);

	initializeOpenGLFunctions();
	glEnable(GL_DEPTH_TEST);
	mProgram = new QOpenGLShaderProgram(this);
	mProgram->addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShaderSource);
	mProgram->addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShaderSource);
	mProgram->link();

	glViewport(0, 0, width(), height());
	float aspectRatio = static_cast<float>(width()) / static_cast<float>(height());
	float nearPlane = 1.0f;
	float farPlane = 1000.0f;
	QMatrix4x4 projectionMatrix;
	projectionMatrix.perspective(45.0f, aspectRatio, nearPlane, farPlane);
	mProgram->setUniformValue(m_projectionMatrixUniform, projectionMatrix);

	m_posAttr = mProgram->attributeLocation("posAttr");
	Q_ASSERT(m_posAttr != -1);
	m_colAttr = mProgram->attributeLocation("colAttr");
	Q_ASSERT(m_colAttr != -1);
	m_normAttr = mProgram->attributeLocation("norAttr");
	Q_ASSERT(m_normAttr != -1);
	m_modelMatrixUniform = mProgram->uniformLocation("modelMatrix");
	Q_ASSERT(m_modelMatrixUniform != -1);
	m_viewMatrixUniform = mProgram->uniformLocation("viewMatrix");
	Q_ASSERT(m_viewMatrixUniform != -1);
	m_projectionMatrixUniform = mProgram->uniformLocation("projMatrix");
	Q_ASSERT(m_projectionMatrixUniform != -1);
	m_normalMatrixUniform = mProgram->uniformLocation("normalMatrix");
	Q_ASSERT(m_normalMatrixUniform != -1);
	m_lightPosUniform = mProgram->uniformLocation("lightPos");
	Q_ASSERT(m_lightPosUniform != -1);
}

void OpenGLWindow::mouseMoveEvent(QMouseEvent* event)
{
	int dx = event->x() - lastPos.x();
	int dy = event->y() - lastPos.y();
	if (event->buttons() & Qt::LeftButton)
	{
		QQuaternion rotX = QQuaternion::fromAxisAndAngle(0.0f, 1.0f, 0.0f, 0.5f * dx);
		QQuaternion rotY = QQuaternion::fromAxisAndAngle(1.0f, 0.0f, 0.0f, 0.5f * dy);

		rotationAngle = rotX * rotY * rotationAngle;
		update();
	}
	lastPos = event->pos();
}

void OpenGLWindow::wheelEvent(QWheelEvent* event)
{
	if (event->angleDelta().y() > 0)
	{
		zoomOut();
	}
	else
	{
		zoomIn();
	}
}

void OpenGLWindow::zoomIn()
{
	scaleFactor *= 1.1f;
	update();
}

void OpenGLWindow::zoomOut()
{
	scaleFactor /= 1.1f;
	update();
}

void OpenGLWindow::setRenderingAttributes(StockMaterial& stock, VoxelGrid& stl, ToolPath& path, ToolCylinder& tool)
{
	mStockMaterialVertices.clear();
	mStockMaterialColors.clear();
	mSTLShapeVertices.clear();
	mSTLShapeColors.clear();
	mPathVers.clear();
	mPathColrs.clear();
	mToolPoles.clear();
	mToolPoleColors.clear();

	mStockMaterialVertices = stock.GridVertices();
	mStockMaterialColors = stock.GridColors();
	mSTLShapeVertices = stl.GridVers();
	mSTLShapeColors = stl.GridColrs();
	mPathVers = path.PathVertices();
	mPathColrs = path.PathColors();
	mToolPoles = tool.PoleVertices();
	mToolPoleColors = tool.PolColors();
}
