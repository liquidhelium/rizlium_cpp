#include "RizPlayer.h"
#include "Rendering.h"
#include "QDebug"

RizPlayer::RizPlayer(QWidget* parent)
	: QGraphicsView(parent)
{
	this->setRenderHint(QPainter::RenderHint::Antialiasing);
	this->gameScene = new QGraphicsScene();
	this->setScene(this->gameScene);
	//this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	this->setDragMode(DragMode::ScrollHandDrag);
	this->fitInView(RENDERING_RECT);
	this->setSceneRect(QRectF(RENDERING_RECT.x(), RENDERING_RECT.y(), RENDERING_RECT.width(), -RENDERING_RECT.height()));
	this->points = std::vector<LinePointItem*>();
	this->canvases = std::vector<Canvas*>();
	this->lineCircles = std::vector<QGraphicsEllipseItem*>();
	this->addTopRect();
	this->addBottomRect();
}

void RizPlayer::addTopRect()
{
	this->rectTop = new QGraphicsRectItem(-RENDERING_RECT.width()*0.5, -RENDERING_RECT.height() * 0.8, 2*RENDERING_RECT.width(), -RENDERING_RECT.height()*0.3);// 不必在意大小 重要的是渐变设置
	auto colorTop = QLinearGradient(0, -RENDERING_RECT.height() * 0.9, 0, -RENDERING_RECT.height());
	colorTop.setColorAt(0, Qt::GlobalColor::transparent);
	colorTop.setColorAt(1, Qt::GlobalColor::white);
	this->rectTop->setPen(QPen(Qt::GlobalColor::transparent));
	this->rectTop->setBrush(QBrush(colorTop));
	this->rectTop->setZValue(1);
	this->gameScene->addItem(rectTop);
}
void RizPlayer::addBottomRect()
{
	this->rectBottom = new QGraphicsRectItem(-RENDERING_RECT.width()*0.5,10,2*RENDERING_RECT.width(), -RENDERING_RECT.height()*0.5); // 不必在意大小 重要的是渐变设置
	auto colorBottom = QLinearGradient(0, -RENDERING_RECT.height() * 0.2, 0, -RENDERING_RECT.height() * 0.4);
	colorBottom.setColorAt(0, Qt::GlobalColor::white);
	colorBottom.setColorAt(1, Qt::GlobalColor::transparent);
	this->rectBottom->setBrush(QBrush(colorBottom));
	this->rectBottom->setPen(QPen(Qt::GlobalColor::transparent));
	this->rectBottom->setZValue(1);
	this->gameScene->addItem(rectBottom);
}
const rizTypes::RizChart* RizPlayer::getChart()
{
	return &this->chart;
}

RizPlayer::RizPlayer(QWidget* parent, rizTypes::RizChart chart)
	: RizPlayer(parent)
{
	this->setChart(chart);
}

void RizPlayer::setChart(rizTypes::RizChart chart)
{
	chart.preprocessChart();
	this->chart = chart;
	reloadChart();
}

void RizPlayer::reloadChart()
{
	clear();
	int pointCount = 0;
	for (int i=0;i < this->chart.canvasMoves.size(); i++)
	{
		auto canvas = new Canvas(&this->chart.canvasMoves.at(i));
		canvas->parentChart = &this->chart;
		this->canvases.push_back(canvas);
	}
	auto initialCirclePos = mapInRenderRect(QPointF(0, 0.25));
	for (int i = 0; i < this->chart.lines.size(); i++)
	{
		// 给这个line准备一个圈
		auto circle = new QGraphicsEllipseItem(initialCirclePos.x(), initialCirclePos.y(), 10, 10);
		circle->setRect(0, initialCirclePos.y(), 40, 40);
		circle->setPen(QPen(this->chart.lines[i].judgeRingColor[0].startColor.toQColor(), 2));
		circle->setZValue(10);
		qDebug() << circle->boundingRect();
		this->fitInView(circle);
		this->lineCircles.push_back(circle);
		this->gameScene->addItem(circle);
		for (int j = 0; j < this->chart.lines[i].linePoints.size(); j++)
		{
			auto item = new LinePointItem(&this->chart.lines[i].linePoints[j]);
			this->points.push_back(item);
			this->canvases.at(item->connectedLinePoint->canvasIndex)->addToGroup(item);
			pointCount++;
			if (j > 0)
			{
				item->setPrevious(this->points.at(pointCount-2));
				this->points.at(pointCount-2)->setNext(item);
			}
		}
	}

	for (int i = 0; i < this->canvases.size(); i++)
		this->gameScene->addItem(this->canvases[i]);

	for (int i = 0; i < this->points.size(); i++)
	{
		this->points[i]->updateRenderPath();
	}
}

void  RizPlayer::timerEvent(QTimerEvent* a0)
{
	if (a0->timerId() == this->updateTimer)
		this->update();
	else
	{
		qDebug() << fpsCount;
		fpsCount = 0;
	}
	QGraphicsView::timerEvent(a0);
}

void RizPlayer::updatePlayer()
{
	fpsCount++;
	if (this->player == nullptr)
		return;
	this->gameChartTime = chart.getChartTime((float)this->player->position() / 1000.0);
	this->gameRealTime = (float)this->player->position() / 1000.0;
	emit this->gameTimeChanged(this->gameChartTime);
	emit this->realTimeChanged(this->gameRealTime);
	if ((int)this->gameRealTime != this->lastRealTimeSec)
	{
		this->lastRealTimeSec = (int)this->gameRealTime;
		emit this->realTimeChanged_sec(this->lastRealTimeSec);
	}
	this->updateCanvases();
	this->updatePoints();
	this->updateLines();
}

void RizPlayer::updateCanvases()
{
	for (int i = 0; i < this->canvases.size(); i++)
		this->canvases[i]->updatePos(this->gameChartTime, this->gameRealTime);

}

void RizPlayer::updatePoints()
{
	for (int i = 0; i < this->points.size(); i++)
		if (!this->points[i]->isSameCanvas() && this->points[i]->isAboutToBeRendered())
		{
			this->points[i]->updateRenderPath();
		}
}

// 更新每条线
void RizPlayer::updateLines()
{
	for (int i = 0; i < this->chart.lines.size(); i++)
	{
		int currentLinePoint = this->chart.lines[i].findLinePoint_time(this->gameChartTime);
		if (currentLinePoint < 0)
			currentLinePoint = 0;
		QPointF localTimePos = this->chart.lines[i].linePoints[currentLinePoint].parentItem->getPosByTime(this->gameChartTime);
		float globalRingXPos = this->chart.lines[i].linePoints[currentLinePoint].parentItem->mapToScene(localTimePos).x();
		// TODO: setX就可以了
		this->lineCircles[i]->setX(globalRingXPos);
	}
}


void RizPlayer::update()
{
	this->updatePlayer();
	QGraphicsView::update();
}

void RizPlayer::resizeEvent(QResizeEvent* ev)
{
	QGraphicsView::resizeEvent(ev);
	this->fitInView(RENDERING_RECT);
}

void RizPlayer::start()
{
	updateTimer =  this->startTimer(1);
	fpsTimer = this->startTimer(1000);
}

void RizPlayer::clear()
{

	for (int i = 0; i < this->points.size(); i++)
	{
		delete points.at(i);
	}
	for (int i = 0; i < this->canvases.size(); i++)
	{
		delete canvases.at(i);
	}
	for (int i = 0; i < this->lineCircles.size(); i++)
	{
		delete lineCircles.at(i);
	}
}

RizPlayer::~RizPlayer()
{
	clear();
	delete this->rectTop;
	delete this->gameScene;
	
}
