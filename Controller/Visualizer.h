#pragma once
#include <QtWidgets/QMainWindow>
#include "Visualizer.h"
#include "DataManager.h"
#include "chrono"
#include "thread"

using namespace std;

class OpenGLWindow;
class DataManager;

class Visualizer : public QMainWindow
{
    Q_OBJECT

public:
    Visualizer(QWindow* parent = nullptr);
    ~Visualizer();

private:
    void setupUi();
    void dataPass();
    void updatePauseResumeTooltip();

private slots:
    void onOpenSTLActionClicked();
    void onSelectToolSizeActionClicked();
    void onSimulateOperationActionClicked();
    void onPauseResumeActionClicked();
    void onFinishAndSaveActionClicked();
    void onShowStockMaterialActionClicked();
    void onShowToolPathActionClicked();
    void onShowSTLShapeActionClicked();

private:
    QMenuBar* mMenuBar;
    QToolBar* mMainToolBar;
    QWidget* mCentralWidget;
    QStatusBar* mStatusBar;
    OpenGLWindow* mRenderer;
    DataManager* mDataManager;
    QAction* mOpenSTLAction;
    QAction* mSelectToolSizeAction;
    QAction* mSimulateOperationAction;
    QAction* mPauseResumeAction;
    QAction* mFinishAndSaveAction;
    QAction* mShowStockMaterialAction;
    QAction* mShowToolPathAction;
    QAction* mShowSTLShapeAction;
    QHBoxLayout* hBox;
    QVBoxLayout* vBox;
    QBoxLayout* mToolLayout;
    QToolBar* toolBar;
    QBoxLayout* contentsLayout;
    string mFilePath;
    bool mIsPaused;
};