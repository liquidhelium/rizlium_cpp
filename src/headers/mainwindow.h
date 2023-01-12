#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "DockManager.h"
#include "GraphicsHierarchy.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

using namespace ads;
class MainWindow : public QMainWindow
{
        Q_OBJECT

        Ui::MainWindow* ui;
        CDockManager* dockingManager;
        CDockWidget* hierarchyWin;
        //CDockWidget* gameWin;
    public:
        MainWindow(QWidget *parent = nullptr);
        ~MainWindow();
        
};
#endif // MAINWINDOW_H
