#ifndef RENDERING_H
#define RENDERING_H
#include <QGraphicsPathItem>
#include <QPainterPath>
#include <QPainter>
#include <functional>
#include "easing.h"
#include "rizTypes.h"
#include "keypointsUtil.h"
QPointF mapInRenderRect(QPointF);
QRectF RENDERING_RECT = QRectF(0, 0, 50 * 9, 50 * 16);

class EasingPath : public QPainterPath
{
public:
	void easingLineTo(Ease func, QPointF to);
	void easingOnlyFirst(Ease func, QPointF to);
	void easingNoFirst(Ease func, QPointF to); // 这两个函数用于不同path的衔接
	EasingPath();
	~EasingPath();
};
class LinePointItem : public QGraphicsEllipseItem
{
	QGraphicsPathItem* path = nullptr;
	LinePointItem* next = nullptr;
	LinePointItem* previous = nullptr;
	bool _isSameCanvas = true; // 对于没有下一个的点 这个值不会被更新 这样的点没有render的必要
	void genPath();
public :
	rizTypes::LinePoint* connectedLinePoint;
	void connectsLinePoint(rizTypes::LinePoint* point);
	QPointF globalPos();
	QPointF getPosByTime(float time);
	void updateRenderPath();
	void updateColor();
	void setNext(LinePointItem* item);
	void setPrevious(LinePointItem* item);
	bool isSameCanvas() { return this->_isSameCanvas; };
	bool isAboutToBeRendered();
	LinePointItem(rizTypes::LinePoint*);
	~LinePointItem();
};

class Canvas : public QGraphicsItemGroup
{
public:
	rizTypes::RizChart* parentChart;
	rizTypes::CanvasMove* moveControl;
	explicit Canvas(QGraphicsItem* parent = nullptr);
	void updatePos(float chartTime, float realTime);
	Canvas(rizTypes::CanvasMove* moveControl,QGraphicsItem* parent = nullptr);
	~Canvas();
};

#endif
