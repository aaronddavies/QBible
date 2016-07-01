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
    _convertText(query, 0, result);
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

void Fetcher::search(QStringList &verses, QStringList &locations, const QString request) {
    QString expression = request;
    expression.replace(' ', '%');
    QSqlQuery query;
    query.prepare("SELECT b, c, v, t from t_web WHERE t LIKE :expr");
    query.bindValue(":expr", expression);
    query.exec();
    _convertText(query, 3, verses);
    _locations(query, locations);
}

void Fetcher::_convertText(QSqlQuery query, int const column, QStringList &result) {
    result.clear();
    QString verse;
    while (query.next()) {
        verse = query.value(column).toString();
        foreach (QString const bad, BAD) {
            verse.replace(QRegularExpression(bad), EMPTY);
        }
        result.append(verse);
    }
}

void Fetcher::_locations(QSqlQuery query, QStringList &result) {
    result.clear();
    while (query.next()) {
        int book = query.value(1).toInt();
        QString title = fetchTitle(book);
        QString loc = QString("%1 %2:%3").arg(title, query.value(2).toString(), query.value(3).toString());
        result.append(loc);
    }
}
