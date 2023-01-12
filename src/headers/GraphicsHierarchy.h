#ifndef GRAPHICSHIERARCHY_H
#define GRAPHICSHIERARCHY_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QTreeView>
#include <QDebug>
#include <QTextStream>
#include <qstandarditemmodel.h>
#include "ui_GraphicsHierarchy.h"
class GraphicsTreeItem: public QStandardItem
{
	QGraphicsItem* item;
	const char* itemTypeHelper(QGraphicsItem* item);
public:
	void setItem(QGraphicsItem* item) { this->item = item; };
	void updateText();
	void updateChilds(int depthNow=0, int depthMax=-1);
	GraphicsTreeItem(QGraphicsItem* item) { this->setItem(item); };
	GraphicsTreeItem() {};
};

class GraphicsSceneHierarchy : public QWidget
{
	Q_OBJECT

	QGraphicsScene* scene;
	QTreeView* view;
	QStandardItemModel* model;
	void genHierarchy();
public:
	void setScene(QGraphicsScene* scene) { this->scene = scene; this->genHierarchy(); };
	GraphicsSceneHierarchy(QWidget *parent = nullptr);
	~GraphicsSceneHierarchy();
public slots:
	void refreshHierarchy();

private:
	Ui::GraphicsHierarchyClass ui;
};
#endif