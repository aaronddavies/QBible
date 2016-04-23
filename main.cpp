#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "ScriptureModel.h"

int main(int argc, char *argv[])
{
    //QGuiApplication app(argc, argv);

    //QQmlApplicationEngine engine;
    //engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    Fetcher::Ptr fetcher(new Fetcher());
    ScriptureModel scripture(fetcher);
    Q_UNUSED(scripture)
    return 0;
    //return app.exec();
}
