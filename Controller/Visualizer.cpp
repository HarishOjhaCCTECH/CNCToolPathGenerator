#include "stdafx.h"
#include "Visualizer.h"
#include "OpenGLWindow.h"



Visualizer::Visualizer(QWindow* parent) : QMainWindow(nullptr), mIsPaused(false)
{
    setupUi();   
}

Visualizer::~Visualizer(){}

void Visualizer::setupUi()
{
    resize(600, 600);

    mMenuBar = new QMenuBar(this);
    setMenuBar(mMenuBar);
    mMainToolBar = new QToolBar(this);
    addToolBar(Qt::TopToolBarArea, mMainToolBar);
    mToolLayout = new QVBoxLayout();
    mToolLayout->setContentsMargins(0, 0, 0, 0);

    toolBar = new QToolBar;
    mToolLayout->addWidget(toolBar);
    contentsLayout = new QVBoxLayout();
    mToolLayout->addLayout(contentsLayout);
    QWidget* centralWidget = new QWidget;
    centralWidget->setLayout(mToolLayout);
    setCentralWidget(centralWidget);


    mOpenSTLAction = new QAction(QIcon("C:/Users/Harish Ojha/Downloads/OpenSTL.png"), "Open Desired STL file", this);
    mSelectToolSizeAction = new QAction(QIcon("C:/Users/Harish Ojha/Downloads/ToolTipSize.png"), "Choose tool size", this);
    mSimulateOperationAction = new QAction(QIcon("C:/Users/Harish Ojha/Downloads/SimulateOperation.png"), "Simulate Operation", this);
    mPauseResumeAction = new QAction(QIcon("C:/Users/Harish Ojha/Downloads/PauseResume.png"), "Pause", this);
    mFinishAndSaveAction = new QAction(QIcon("C:/Users/Harish Ojha/Downloads/FinishAndSave.png"), "Finish and save the tool path generated", this);
    mShowStockMaterialAction = new QAction(QIcon("C:/Users/Harish Ojha/Downloads/ShowStockMaterial.png"), "Show stock material", this);
    mShowToolPathAction = new QAction(QIcon("C:/Users/Harish Ojha/Downloads/ShowToolPath.png"), "Show tool path", this);
    mShowSTLShapeAction = new QAction(QIcon("C:/Users/Harish Ojha/Downloads/ShowSTLShape.png"), "Show STL Shape", this);

    connect(mOpenSTLAction, &QAction::triggered, this, &Visualizer::onOpenSTLActionClicked);
    connect(mSelectToolSizeAction, &QAction::triggered, this, &Visualizer::onSelectToolSizeActionClicked);
    connect(mSimulateOperationAction, &QAction::triggered, this, &Visualizer::onSimulateOperationActionClicked);
    connect(mPauseResumeAction, &QAction::triggered, this, &Visualizer::onPauseResumeActionClicked);
    connect(mFinishAndSaveAction, &QAction::triggered, this, &Visualizer::onFinishAndSaveActionClicked);
    connect(mShowStockMaterialAction, &QAction::triggered, this, &Visualizer::onShowStockMaterialActionClicked);
    connect(mShowToolPathAction, &QAction::triggered, this, &Visualizer::onShowToolPathActionClicked);
    connect(mShowSTLShapeAction, &QAction::triggered, this, &Visualizer::onShowSTLShapeActionClicked);

    mMainToolBar->addAction(mOpenSTLAction);
    mMainToolBar->addAction(mSelectToolSizeAction);
    mMainToolBar->addAction(mSimulateOperationAction);
    mMainToolBar->addAction(mPauseResumeAction);
    updatePauseResumeTooltip();
    mMainToolBar->addAction(mFinishAndSaveAction);
    mMainToolBar->addAction(mShowStockMaterialAction);
    mMainToolBar->addAction(mShowToolPathAction);
    mMainToolBar->addAction(mShowSTLShapeAction);


    mStatusBar = new QStatusBar(this);
    setStatusBar(mStatusBar);
    mRenderer = new OpenGLWindow(QColor(0, 0, 0), this);
    setCentralWidget(mRenderer);
    setWindowTitle(QCoreApplication::translate("CNC Tool Path Generator", "CNC Tool Path Generator", nullptr));
    
}

void Visualizer::dataPass()
{

    mRenderer->setRenderingAttributes(mDataStorage->stockMaterial(), mDataStorage->toolCylinder(), mDataStorage->generatedToolPath());
}

void Visualizer::onOpenSTLActionClicked()
{
    QStringList shapes;
    shapes << "Cube" << "Sphere";
    bool ok;
    QString shape = QInputDialog::getItem(this, "Select Shape", "Choose a shape:", shapes, 0, false, &ok);
    if (ok && !shape.isEmpty()) {
        if (shape == "Cube") {
            mDataStorage = new DataStorage(this);
            mDataStorage->setShapeFilePath("/Model/Cube.stl");
            
        }
        else if (shape == "Sphere") {
            mDataStorage = new DataStorage(this);
            mDataStorage->setShapeFilePath("/Model/Sphere.stl");
            mDataStorage->processData();
            dataPass();
            mRenderer->update();
        }
        else if (shape == "Cylinder") {
    
        }
        else if (shape == "Custom") {
    
        }
    }
}

void Visualizer::onSelectToolSizeActionClicked()
{
    QStringList sizes;
    sizes << "10" << "20" << "30" << "size4";
    bool ok;
    QString size = QInputDialog::getItem(this, "Select Tool Size", "Choose a size:", sizes, 0, false, &ok);
    if (ok && !size.isEmpty()) {
        if (size == "10") {
            mDataStorage->setToolSize(size.toFloat());
            mDataStorage->processData();
            dataPass();
            mRenderer->update();
        }
        else if (size == "20") {
            mDataStorage->setToolSize(size.toFloat());
            mDataStorage->processData();
            dataPass();
            mRenderer->update();
        }
        else if (size == "30") {
            
        }
        else if (size == "40") {
            
        }
    }
}

void Visualizer::onSimulateOperationActionClicked()
{
    //
    
}

void Visualizer::onPauseResumeActionClicked()
{
    mIsPaused = !mIsPaused;
    updatePauseResumeTooltip();
 
}
void Visualizer::onFinishAndSaveActionClicked()
{

}

void Visualizer::updatePauseResumeTooltip()
{
    if (mIsPaused)
        mPauseResumeAction->setToolTip("Resume");
    else
        mPauseResumeAction->setToolTip("Pause");
}

void Visualizer::onShowStockMaterialActionClicked()
{

}
void Visualizer::onShowToolPathActionClicked()
{

}
void Visualizer::onShowSTLShapeActionClicked()
{

}