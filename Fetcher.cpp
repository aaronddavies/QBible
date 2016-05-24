#include "Fetcher.h"
#include <QRegularExpression>

Fetcher::Fetcher(QObject *parent) :
    QObject(parent),
    _db()
{
    _db = QSqlDatabase::addDatabase("QSQLITE");
    _db.setHostName("bibledb");
    _db.setDatabaseName("bible.db");
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
    while (query.next()) {
        verse = query.value(0).toString();
        foreach (QString const bad, BAD) {
            verse.replace(QRegularExpression(bad), EMPTY);
        }
        result.append(verse);
    }
}

QString Fetcher::fetchTitle(const int book) {
    QSqlQuery query;
    query.prepare("SELECT n from key_english WHERE b IS :book");
    query.bindValue(":book", book);
    query.exec();

    query.next();
    return query.value(0).toString();
}

int Fetcher::chapterCount(const int book) {
    QSqlQuery query;
    query.prepare("SELECT MAX(c) from t_web WHERE b IS :book");
    query.bindValue(":book", book);
    query.exec();

    query.next();
    return query.value(0).toInt();
}
