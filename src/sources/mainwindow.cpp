#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "GameView.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->dockingManager = new CDockManager(this);
    this->hierarchyWin = new CDockWidget("Hierarchy");
    auto hierarchyWidget = new GraphicsSceneHierarchy();
    this->hierarchyWin->setWidget(hierarchyWidget);
    this->dockingManager->addDockWidget(TopDockWidgetArea, this->hierarchyWin);
    this->ui->menubar->addAction(hierarchyWin->toggleViewAction());
    auto gameWidget = new GameView();
    auto gameWin = new CDockWidget("game");
    gameWin->setWidget(gameWidget);
    hierarchyWidget->setScene(gameWidget->player()->scene());
    this->dockingManager->addDockWidget(LeftDockWidgetArea, gameWin);
    this->ui->menubar->addAction(gameWin->toggleViewAction());
    // QObject::connect(gameWidget->player(), &RizPlayer::realTimeChanged_sec, hierarchyWidget, &GraphicsSceneHierarchy::refreshHierarchy);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete dockingManager;
}

