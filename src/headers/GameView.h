#ifndef GAMEVIEW_H
#define GAMEVIEW_H
#include <qwidget.h>
#include <RizPlayer.h>
QT_BEGIN_NAMESPACE
namespace Ui { class gameWindow; }
QT_END_NAMESPACE
class GameView :
    public QWidget
{
    Q_OBJECT
    Ui::gameWindow* ui;
public :
    RizPlayer* player();
    GameView(QWidget* parent = nullptr);
public slots:
    void moveSliderByTime(float);
};
#endif 
