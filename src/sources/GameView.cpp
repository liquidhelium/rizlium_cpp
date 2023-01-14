#include "GameView.h"
#include "QtMultimedia/qaudio.h"
#include "ui_GameWindow.h"
#include <QAudioOutPut>
#include <QFile>

RizPlayer* GameView::player()
{
    return this->ui->ResizeChild;
}

GameView::GameView(QWidget* parent)
	: QWidget(parent)
	, ui(new Ui::gameWindow)
{
	ui->setupUi(this);
    RizPlayer* player = ui->ResizeChild;

    using rizTypes::RizChart;
    using json = nlohmann::json;
    QFile file(":/assets/assets/chart.json");
    if (!file.open(QIODevice::ReadOnly))
    {
        qFatal("Cant read chart! Exiting...");
    }
    auto str = file.readAll();
    json chart = json::parse(str);
    RizChart rizChart;
    rizTypes::from_json(chart, rizChart);
    auto pl = new QMediaPlayer();
    auto ct = QUrl("qrc:///assets/assets/take.wav");
    pl->setSource(ct);
    pl->audioOutput()->setVolume(QAudio::convertVolume(0.01, QAudio::LinearVolumeScale, QAudio::LogarithmicVolumeScale));
    pl->play();
    player->player = pl;
    player->setChart(rizChart);
    if (!pl->hasAudio())
        qDebug() << "?";
    QObject::connect(pl, &QMediaPlayer::hasAudioChanged,player, & RizPlayer::start);
}

void GameView::moveSliderByTime(float time)
{
    this->ui->horizontalSlider->setValue((int)time);
}
