#include "stdafx.h"
#include "Visualizer.h"
#include "OpenGLWindow.h"

void delay(int milliseconds) {
    std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}

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

    QString currentPathIcon = QCoreApplication::applicationDirPath();
    QDir dir(currentPathIcon);
    dir.cdUp();
    dir.cdUp();
    QString parentPathIcon = dir.path();




    mOpenSTLAction = new QAction(QIcon(parentPathIcon+"/Model/Icons/OpenSTL.png"), "Open Desired STL file", this);
    mSelectToolSizeAction = new QAction(QIcon(parentPathIcon + "/Model/Icons/ToolTipSize.png"), "Choose tool size", this);
    mSimulateOperationAction = new QAction(QIcon(parentPathIcon + "/Model/Icons/SimulateOperation.png"), "Simulate Operation", this);
    mPauseResumeAction = new QAction(QIcon(parentPathIcon + "/Model/Icons/PauseResume.png"), "Pause", this);
    mFinishAndSaveAction = new QAction(QIcon(parentPathIcon + "/Model/Icons/FinishAndSave.png"), "Finish and save the tool path generated", this);
    mShowStockMaterialAction = new QAction(QIcon(parentPathIcon + "/Model/Icons/ShowStockMaterial.png"), "Show stock material", this);
    mShowToolPathAction = new QAction(QIcon(parentPathIcon + "/Model/Icons/ShowToolPath.png"), "Show tool path", this);
    mShowSTLShapeAction = new QAction(QIcon(parentPathIcon + "/Model/Icons/ShowSTLShape.png"), "Show STL Shape", this);

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

    mRenderer->setRenderingAttributes(mDataManager->stockMaterial(), mDataManager->toolCylinder(), mDataManager->generatedToolPath());
}

void Visualizer::onOpenSTLActionClicked()
{
    
    QString filePath = QFileDialog::getOpenFileName(this, tr("Open STL File"), "C:/Users/Harish Ojha/Downloads", tr("STL Files (*.stl)"));
    if (!filePath.isEmpty()) {
        qDebug() << "Selected file: " << filePath;
    }
    mFilePath = filePath.toStdString();
}

void Visualizer::onSelectToolSizeActionClicked()
{
    
    
    QStringList sizes;
    sizes << "10" << "20" << "30" << "size4";
    bool ok;
    QString size = QInputDialog::getItem(this, "Select Tool Size", "Choose a size:", sizes, 0, false, &ok);
    if (ok && !size.isEmpty()) {
        if (size == "10") {
            mDataManager = new DataManager(this);
            // mDataManager->setToolSize(size.toFloat());
            mDataManager->processData(size.toInt(), mFilePath);
            dataPass();
            mRenderer->mShowStockMaterial = true;
            mRenderer->mShowSTL = true;
            mRenderer->mShowToolPath = true;
            mRenderer->mShowToolCylinder = true;
            mRenderer->update();
        }
        else if (size == "20") {
            mDataManager->setToolSize(size.toFloat());
            mDataManager->processData(10, mFilePath);
            dataPass();
            mRenderer->mShowStockMaterial = true;
            mRenderer->mShowSTL = true;
            mRenderer->mShowToolPath = true;
            mRenderer->mShowToolCylinder = true;
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
    mRenderer->mShowSimulation = true;
    mRenderer->mShowStockMaterial = true;
    mRenderer->mShowSTL = true;
    mRenderer->mShowToolPath = true;
    mRenderer->mShowToolCylinder = true;
    
    for (int i = 0; i < 5; i++)//mRenderer->toolPathVerticesSize() / 3
    {
        mDataManager->simulate();
        dataPass();
        mRenderer->update();
        delay(1000);
        QCoreApplication::processEvents();
        if (!mRenderer->mShowSimulation)
        {
            break;
        }
    }    
}

void Visualizer::onPauseResumeActionClicked()
{
    mIsPaused = !mIsPaused;
    updatePauseResumeTooltip();
}
void Visualizer::onFinishAndSaveActionClicked()
{
    mRenderer->mShowSimulation = false;
    mRenderer->mShowStockMaterial = false;
    mRenderer->mShowSTL = false;
    mRenderer->mShowToolPath = false;
    mRenderer->mShowToolCylinder = false;
    mRenderer->update();
    QCoreApplication::processEvents();
    mDataManager->savefile();
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
    mRenderer->mShowStockMaterial = true;
    mRenderer->mShowSTL = false;
    mRenderer->mShowToolPath = false;
    mRenderer->mShowToolCylinder = false;
    mRenderer->update();
}
void Visualizer::onShowToolPathActionClicked()
{
    mRenderer->mShowStockMaterial = false;
    mRenderer->mShowSTL = false;
    mRenderer->mShowToolPath = true;
    mRenderer->mShowToolCylinder = false;
    mRenderer->update();
}
void Visualizer::onShowSTLShapeActionClicked()
{
    mRenderer->mShowStockMaterial = false;
    mRenderer->mShowSTL = true;
    mRenderer->mShowToolPath = false;
    mRenderer->mShowToolCylinder = false;
    mRenderer->update();
}

