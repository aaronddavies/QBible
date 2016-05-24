#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "ScriptureModel.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    Fetcher::Ptr fetcher(new Fetcher());
    ScriptureModel scripture(fetcher);

    QQmlApplicationEngine engine;
    QQmlContext *context = engine.rootContext();
    context->setContextProperty("scripture_model", &scripture);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    app.exec();
}
