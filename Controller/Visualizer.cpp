#include "stdafx.h"
#include "Visualizer.h"
#include "OpenGLWindow.h"

// delay function tool cylinder movement
void delay(int milliseconds) {
    this_thread::sleep_for(chrono::milliseconds(milliseconds));
}

Visualizer::Visualizer(QWindow* parent) : QMainWindow(nullptr), mIsPaused(false), mDataManager(new DataManager()), mRenderer(new OpenGLWindow(QColor(0, 0, 0), this))
{
    setupUi();
}

Visualizer::~Visualizer() {}

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

    // finding file path of icons
    QString currentPathIcon = QCoreApplication::applicationDirPath();
    QDir dir(currentPathIcon);
    dir.cdUp();
    dir.cdUp();
    QString parentPathIcon = dir.path();

    // Icons of the QAction buttons
    mOpenSTLAction = new QAction(QIcon(parentPathIcon + "/Resources/Icons/OpenSTL.png"), "Open Desired STL file", this);
    mSelectToolSizeAction = new QAction(QIcon(parentPathIcon + "/Resources/Icons/ToolTipSize.png"), "Choose tool size", this);
    mSimulateOperationAction = new QAction(QIcon(parentPathIcon + "/Resources/Icons/SimulateOperation.png"), "Simulate Operation", this);
    mPauseResumeAction = new QAction(QIcon(parentPathIcon + "/Resources/Icons/PauseResume.png"), "Pause", this);
    mFinishAndSaveAction = new QAction(QIcon(parentPathIcon + "/Resources/Icons/FinishAndSave.png"), "Finish and save the tool path generated", this);
    mShowStockMaterialAction = new QAction(QIcon(parentPathIcon + "/Resources/Icons/ShowStockMaterial.png"), "Show stock material", this);
    mShowToolPathAction = new QAction(QIcon(parentPathIcon + "/Resources/Icons/ShowToolPath.png"), "Show tool path", this);
    mShowSTLShapeAction = new QAction(QIcon(parentPathIcon + "/Resources/Icons/ShowSTLShape.png"), "Show STL Shape", this);

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
    
    setCentralWidget(mRenderer);
    setWindowTitle(QCoreApplication::translate("CNC Tool Path Generator", "CNC Tool Path Generator", nullptr));
}

void Visualizer::dataPass()
{
    mRenderer->setRenderingAttributes(mDataManager->Stock(), mDataManager->StlVoxels(), mDataManager->Path(), mDataManager->Tool());
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
    bool ok;
    QString size = QInputDialog::getText(this, "Select Tool Size", "Enter a size:", QLineEdit::Normal, QString(), &ok);
    if (ok && !size.isEmpty()) {
        double sizeValue = size.toDouble(&ok);
        if (ok) {
            const double minimumSize = 4.0; // minimum value of tool
            if (sizeValue >= minimumSize) {
                mToolSize = sizeValue;
                mDataManager->processData(sizeValue, mFilePath);
                dataPass();
                mRenderer->mShowStockMaterial = true;
                mRenderer->mShowSTL = true;
                mRenderer->mShowToolPath = true;
                mRenderer->mShowToolCylinder = true;
                mRenderer->update();
            }
            else {
                // Handle value below minimum
                QMessageBox::warning(this, "Invalid Input", "Please enter a value greater than or equal to " + QString::number(minimumSize) + ".");
            }
        }
        else {
            // Handle invalid input
            QMessageBox::warning(this, "Invalid Input", "Please enter a valid number.");
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

    int movement = mDataManager->Path().PathVertices().size()/3;
    for (int i = 0; i < movement; i++)
    {
        mDataManager->simulate(mToolSize, i);
        dataPass();
        mRenderer->update();
        delay(1000);
        QCoreApplication::processEvents();
        if (!mRenderer->mShowSimulation) { break; }
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
    //mDataManager->savefile();
}

void Visualizer::updatePauseResumeTooltip()
{
    if (mIsPaused) {
        mPauseResumeAction->setToolTip("Resume");
    }
    else {
        mPauseResumeAction->setToolTip("Pause");
    }
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
