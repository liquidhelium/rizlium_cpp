#ifndef KEEPRATIOWITGET_H
#define KEEPRATIOWITGET_H

#include <QWidget>
#include <qevent.h>

class KeepRatioWidget : public QWidget
{
	Q_OBJECT

public:
	int widthRatio=9;
	int heightRatio=16;
	void setRatio(int width, int height);
	KeepRatioWidget(QWidget *parent = nullptr);
	~KeepRatioWidget();
	virtual void resizeEvent(QResizeEvent* ev);
};
#endif