#pragma once
#include <QtWidgets/QMainWindow>
#include "Visualizer.h"
#include "Voxel.h"
#include "DataStorage.h"

class OpenGLWindow;
class DataStorage;

class Visualizer : public QMainWindow
{
    Q_OBJECT

public:
    Visualizer(QWindow* parent = nullptr);
    ~Visualizer();
    void dataPass();
    

private:
    void setupUi();

private:
    QMenuBar* mMenuBar;
    QToolBar* mMainToolBar;
    QWidget* mCentralWidget;
    QStatusBar* mStatusBar;
    OpenGLWindow* mRenderer;
    DataStorage* mDataStorage;
    



};