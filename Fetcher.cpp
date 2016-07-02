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
    while (query.next()) {
        result.append(_convertText(query.value(0)));
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

void Fetcher::search(QStringList &verses, QStringList &locations, const QString request) {
    QString expression = request;
    expression.replace(' ', '%');
    QSqlQuery query;
    query.prepare(QString("SELECT b, c, v, t from t_web WHERE t LIKE '\%%1\%'").arg(expression));
    query.exec();
    verses.clear();
    locations.clear();
    while (query.next()) {
        verses.append(_convertText(query.value(3)));
        locations.append(_locationDisplay(query.value(0), query.value(1), query.value(2)));
    }
}

QString Fetcher::_convertText(QVariant const value) {
    QString verse = value.toString();
    foreach (QString const bad, BAD) {
        verse.replace(QRegularExpression(bad), EMPTY);
    }
    return verse;
}

QString Fetcher::_locationDisplay(QVariant const book, QVariant const chapter, QVariant const verse) {
    QString title = fetchTitle(book.toInt());
    return QString("%1 %2:%3").arg(title, chapter.toString(), verse.toString());
}
