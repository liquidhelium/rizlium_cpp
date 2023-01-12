#ifndef RIZPLAYER_H
#define RIZPLAYER_H
#include <QGraphicsView>
#include <QTime>
#include <qevent.h>
#include <QMediaPlayer>
#include "rizTypes.h"
#include "Rendering.h"

class RizPlayer  : public QGraphicsView
{
	Q_OBJECT
		rizTypes::RizChart chart;
	int fpsCount;
	int updateTimer;
	int fpsTimer;
	float gameChartTime = 0;
	float gameRealTime = 0;
	int lastRealTimeSec = 0;
	void clear();
	void updateCanvases();
	void updatePoints();
	void updateLines();
public:
	QGraphicsScene* gameScene;
	std::vector<LinePointItem*> points;
	std::vector<Canvas*> canvases;
	std::vector<QGraphicsEllipseItem*> lineCircles;
	QGraphicsRectItem* rectBottom;
	QGraphicsRectItem* rectTop;
	QMediaPlayer* player = nullptr;
	virtual void timerEvent(QTimerEvent* ev);
	void update();
	RizPlayer();
	RizPlayer(QWidget *parent);
	RizPlayer(QWidget* parent, rizTypes::RizChart chart);
	void addTopRect();
	void addBottomRect();
	virtual void resizeEvent(QResizeEvent* ev);
	void setChart(rizTypes::RizChart chart);
	void reloadChart();
	const rizTypes::RizChart* getChart();
	~RizPlayer();
signals:
	void gameTimeChanged(float);
	void realTimeChanged(float);
	void realTimeChanged_sec(int);
public slots:
	void updatePlayer();
	void start();
};
#endif