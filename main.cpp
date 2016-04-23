#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "Fetcher.h"

int main(int argc, char *argv[])
{
    //QGuiApplication app(argc, argv);

    //QQmlApplicationEngine engine;
    //engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    Fetcher scripture;
    QStringList chapter;
    scripture.fetchChapter(chapter, 1, 1);
    return 0;
    //return app.exec();
}
