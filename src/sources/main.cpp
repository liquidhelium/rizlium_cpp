#include "mainwindow.h"

#pragma comment(lib, "qtadvanceddocking.lib")

#include <QApplication>
#include <QString>
#include <QFile>
#include <QDebug>
#include <QMediaPlayer>
#include <qevent.h>
#include <QResource>
#include "rizTypes.h"
#include "nlohmann/json.hpp"
#include "RizPlayer.h"
#include "DockManager.h"
void testChart();
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QResource::registerResource(qApp->applicationDirPath().append("/assets/music.rcc"));
    MainWindow w;
    w.show();
    return a.exec();
}

void testChart()
{
    using rizTypes::RizChart;
    using json = nlohmann::json;
    using std::ifstream;
    QFile file(":assets/assets/chart.json");
    auto str = file.readAll();
    json chart = json::parse(str);
    RizChart rizChart;
    rizTypes::from_json(chart, rizChart);
    json j1;
    rizTypes::to_json(j1, rizChart);
    QString str1 = j1.dump().c_str();
    qDebug() << str1;
}
