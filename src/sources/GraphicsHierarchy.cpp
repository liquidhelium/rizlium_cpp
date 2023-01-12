#include "GraphicsHierarchy.h"

void _iterItem(QStandardItem* item);

void GraphicsSceneHierarchy::genHierarchy()
{
	if (this->scene == nullptr)
		return;
	this->model = new QStandardItemModel();
	foreach(QGraphicsItem * (item), this->scene->items())
	{
		if (item->parentItem())
			continue;
		auto treeItem = new GraphicsTreeItem(item);
		treeItem->updateText();
		treeItem->updateChilds();
		model->appendRow(treeItem);
	}
	this->view->setModel(model);
}
void GraphicsSceneHierarchy::refreshHierarchy()
{
	_iterItem(this->model->invisibleRootItem());
}

GraphicsSceneHierarchy::GraphicsSceneHierarchy(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	this->view = this->findChild<QTreeView*>("mainTreeView");
	if (view == nullptr)
		qWarning() << "GraphicsSceneHierarchy: no such child";
}

GraphicsSceneHierarchy::~GraphicsSceneHierarchy()
{
	delete this->model;
}

const char* GraphicsTreeItem::itemTypeHelper(QGraphicsItem* item)
{
	switch (item->type())
	{
		case int(QGraphicsEllipseItem::Type): 
			return "QGraphicsEllipseItem";
		case int(QGraphicsPathItem::Type) :
			return "QGraphicsPathItem";
		case int(QGraphicsRectItem::Type) :
			return "QGraphicsRectItem";
		case int(QGraphicsItemGroup::Type) :
			return "QGraphicsItemGroup";
	default:
		return "<Unchecked>";
	}
}

void GraphicsTreeItem::updateText()
{
	QString str;
	QDebug(&str) << itemTypeHelper(this->item) << this->item;
	this->setText(str);
}

void GraphicsTreeItem::updateChilds(int depthNow, int depthMax)
{
	if (depthMax != -1 && depthNow > depthMax)
		return;
	foreach(QGraphicsItem * (childItem), item->childItems())
	{
		auto treeItemChild = new GraphicsTreeItem(childItem);
		treeItemChild->updateText();
		treeItemChild->updateChilds(depthNow + 1, depthMax);
		this->appendRow(treeItemChild);
	}
}

void _iterItem(QStandardItem* item)
{
	Q_ASSERT(item);
	if (item->hasChildren())
	{
		for (int i = 0; i < item->rowCount(); i++)
		{
			GraphicsTreeItem* childitem = static_cast<GraphicsTreeItem*>( item->child(i));
			childitem->updateText();
			_iterItem(childitem);
		}
	}
}