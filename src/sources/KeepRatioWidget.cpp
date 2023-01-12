#include "KeepRatioWidget.h"

KeepRatioWidget::KeepRatioWidget(QWidget *parent)
	: QWidget(parent)
{
}

KeepRatioWidget::~KeepRatioWidget()
{}

void KeepRatioWidget::setRatio(int width, int height)
{
	this->widthRatio = width;
	this->heightRatio = width;
}

void KeepRatioWidget::resizeEvent(QResizeEvent * ev)
{
	QSize old = ev->size();
	QSize now = ev->size();
	QWidget* child = this->findChild<QWidget*>("ResizeChild");
	if (child != nullptr)
	{

		if (now.width() < widthRatio * now.height() / heightRatio) {
			//宽度不足，则以宽度来计算
			now.setHeight(heightRatio * now.width() / widthRatio);
			//竖直方向居中
			child->move(0, (old.height() - now.height()) / 2);

		}
		else {
			//否则以高度来计算
			now.setWidth(widthRatio * now.height() / heightRatio);
			//水平方向居中
			child->move((old.width() - now.width()) / 2, 0);

		}

		child->resize(now);
	}
}
