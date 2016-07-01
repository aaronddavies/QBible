#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "ScriptureModel.h"
#include "SearchModel.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    Fetcher::Ptr fetcher(new Fetcher());
    ScriptureModel scripture(fetcher);
    SearchModel search(fetcher);

    QQmlApplicationEngine engine;
    QQmlContext *context = engine.rootContext();
    context->setContextProperty("scripture_model", &scripture);
    context->setContextProperty("search_model", &search);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    app.exec();
}
