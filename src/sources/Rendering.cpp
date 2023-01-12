#include "Rendering.h"



QPointF mapInRenderRect(QPointF point)
{
	return QPointF(
		RENDERING_RECT.width() * (point.x()+0.5),
		-RENDERING_RECT.height() * (point.y())
	);
}

EasingPath::EasingPath()
{}

EasingPath::~EasingPath()
{}

// 每一条线用多少顶点
const int SEGMENTS = 50;

// 以 func 这个 函数, 画一个函数图像到to点
// 假设 func 是标准化的函数 (输入值在0~1, 输出值中 0~1对应始终)
// 以纵轴为x, 也就是说easing都将是控制左右形状的
void EasingPath::easingLineTo(Ease func, QPointF to)
{
	auto current = this->currentPosition();
	for (int i = 0; i <= SEGMENTS; i++)
	{
		float progress = (float)i / (float)SEGMENTS;
		this->lineTo(
			lerp(current.x(), to.x(), func(progress)),
			lerp(current.y(), to.y(), progress)
		);
	}
}

// 仅第一分段的easingLine, 用于平滑连接不同的line 
void EasingPath::easingOnlyFirst(Ease func, QPointF to)
{
	this->lineTo(
		lerp(this->currentPosition().x(), to.x(), func((float)1 / (float)SEGMENTS)),
		lerp(this->currentPosition().y(), to.y(), (float)1 / (float)SEGMENTS)
	);
}

// 无第一分段的easingLine, 用于平滑连接不同的line 
void EasingPath::easingNoFirst(Ease func, QPointF to)
{
	auto current = this->currentPosition();
	for (int i = 1; i <= SEGMENTS; i++)
	{
		float progress = (float)i / (float)SEGMENTS;
		this->lineTo(
			lerp(current.x(), to.x(), func(progress)),
			lerp(current.y(), to.y(), progress)
		);
	}
}

// 用于初始化的调用
void LinePointItem::genPath()
{
	if (this->next != nullptr && this->path == nullptr)
	{
		this->path = new QGraphicsPathItem(this);
		this->updateRenderPath();
	}
	if (this->path != nullptr)
	{
		this->path->setPos(0, 0);
		this->updateColor();
	}
}

// 更新线的形状 (仅本段)
void LinePointItem::updateRenderPath()
{
	if (this->path != nullptr)
	{
		auto easingPath = EasingPath();
		easingPath.moveTo(0, 0);
		if (this->previous != nullptr)
		{
			easingPath.easingNoFirst(easing[this->connectedLinePoint->easeType], mapFromItem(this->next, 0, 0));
		}
		else
		{
			easingPath.easingLineTo(easing[this->connectedLinePoint->easeType], mapFromItem(this->next, 0, 0));
		}

		if (this->next->next != nullptr)
			easingPath.easingOnlyFirst(easing[this->next->connectedLinePoint->easeType], mapFromItem(this->next->next, 0, 0));
		this->path->setPath(easingPath);
	}
	else
		genPath();
}

// 更新线的颜色 (渐变, 目前不带lineColor混合)
void LinePointItem::updateColor()
{
	auto gradient = QLinearGradient();
	gradient.setStart(this->globalPos());
	gradient.setFinalStop(this->next->globalPos());
	gradient.setColorAt(0, this->connectedLinePoint->color.toQColor());
	gradient.setColorAt(1, this->next->connectedLinePoint->color.toQColor());
	this->path->setPen(QPen(QBrush(gradient), 10));
}

// 根据绝对时间取此时线上的相对位置
QPointF LinePointItem::getPosByTime(float time)
{
	if (this->next == nullptr)
		return QPointF(0,0);

	if (!liesBetween(this->connectedLinePoint->time, this->next->connectedLinePoint->time, time))
	{
		//qWarning() << "传入了不在区间内的时间"<< this->connectedLinePoint->time <<" " << time << " " << this->next->connectedLinePoint->time;
		return QPointF(0,0);
	}
	float timeOffset = time - this->connectedLinePoint->time;
	float timeFull = this->next->connectedLinePoint->time - this->connectedLinePoint->time;
	// 不可能出现除零的, 上面已经保证了time在区间内(区间肯定是非空的区间)
	float normalizedTime = timeOffset / timeFull;
	QPointF toPos = mapFromItem(this->next, 0, 0);
	return QPointF(lerp(0, toPos.x(), easing[this->connectedLinePoint->easeType](normalizedTime)),
		lerp(0, toPos.y(), normalizedTime));
}

void LinePointItem::connectsLinePoint(rizTypes::LinePoint* point)
{
	this->connectedLinePoint = point;
	point->parentItem = this;
}

QPointF LinePointItem::globalPos()
{
	return this->mapToScene(0,0);
}

LinePointItem::LinePointItem(rizTypes::LinePoint* point)
	:QGraphicsEllipseItem()
{
	this->connectsLinePoint(point);
	auto pos = QPointF(point->xPosition, point->floorPosition);
	pos = mapInRenderRect(pos);
	this->setRect(0, 0, 10, 10);
	this->setPos(pos);
}

void LinePointItem::setNext(LinePointItem* item)
{
	this->next = item;
	if (item->connectedLinePoint->canvasIndex == this->connectedLinePoint->canvasIndex)
		this->_isSameCanvas = true;
	else
		this->_isSameCanvas = false;
}
void LinePointItem::setPrevious(LinePointItem* item)
{
	this->previous = item;
}

bool LinePointItem::isAboutToBeRendered()
{
	return -this->globalPos().y() > RENDERING_RECT.top() &&
		-this->globalPos().y() < RENDERING_RECT.bottom();
}


LinePointItem::~LinePointItem()
{
	delete this->path;
}

Canvas::Canvas(QGraphicsItem* parent)
	:QGraphicsItemGroup(parent)
{}

Canvas::~Canvas()
{}

void Canvas::updatePos(float chartTime,float realTime)
{
	float x = getValue(this->moveControl->xPositionKeyPoints,chartTime);
	float y = getIntegration(this->moveControl->speedKeyPoints, realTime);
	this->setPos(mapInRenderRect(QPointF(x-0.5, -y+0.3)));
}


Canvas::Canvas(rizTypes::CanvasMove* moveControl, QGraphicsItem* parent):
	Canvas(parent)
{
	this->moveControl = moveControl;
}
