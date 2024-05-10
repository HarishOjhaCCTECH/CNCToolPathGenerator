#pragma once
#include <QtWidgets/QMainWindow>
#include "Visualizer.h"
#include "Voxel.h"

class OpenGLWindow;

class Visualizer : public QMainWindow
{
    Q_OBJECT

public:
    Visualizer(QWindow* parent = nullptr);
    ~Visualizer();
    void dataPass(Voxel& stockMaterial);

private:
    void setupUi();

private:
    QMenuBar* mMenuBar;
    QToolBar* mMainToolBar;
    QWidget* mCentralWidget;
    QStatusBar* mStatusBar;
    OpenGLWindow* mRenderer;



};