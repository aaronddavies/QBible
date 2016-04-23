#include "Fetcher.h"
#include <QRegularExpression>

Fetcher::Fetcher(QObject *parent) :
    QObject(parent),
    _db()
{
    _db = QSqlDatabase::addDatabase("QSQLITE");
    _db.setHostName("bibledb");
    _db.setDatabaseName("bible-sqlite.db");
    Q_ASSERT(_db.open());  // should be bundled in executable
}

Fetcher::~Fetcher() {

}

void Fetcher::fetchChapter(QStringList &result, const int book, const int chapter) {
    QSqlQuery query;
    query.prepare("SELECT t from t_web WHERE b IS :book AND c IS :chapter");
    query.bindValue(":book", book);
    query.bindValue(":chapter", chapter);
    query.exec();

    result.clear();
    QString verse;
    QRegularExpression re("{.*}");
    while (query.next()) {
        verse = query.value(0).toString();
        verse.replace(re, "");
        result.append(verse);
    }
    qDebug() << result;
}
