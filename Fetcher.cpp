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

void Fetcher::search(QStringList &verses, QStringList &locations, QString request) {
    verses.clear();
    locations.clear();
    _cleanSearchText(request);
    if (request.isEmpty()) { return; }
    QSqlQuery query;
    QString queryString = QString("SELECT b, c, v, t from t_web WHERE t LIKE '\%%1\%'").arg(request);
    query.prepare(queryString);
    query.exec();
    while (query.next()) {
        QString verse = _convertText(query.value(3));
        if (!_highlightSearchWords(verse, request)) { continue; }
        verses.append(verse);
        locations.append(_locationDisplay(query.value(0), query.value(1), query.value(2)));
    }
}

int Fetcher::_highlightSearchWords(QString &verse, const QString request) {
    QStringList keywords = request.split(SQL_DELIMITER);
    int highlight_count = 0;
    foreach (QString const key, keywords) {
        if (key.isEmpty()) { continue; }
        int loc = verse.indexOf(key, 0, Qt::CaseInsensitive);
        while (loc >= 0) {
            verse.insert(loc, BEGIN_HIGHLIGHT);
            verse.insert(loc + key.length() + BEGIN_HIGHLIGHT.length(), END_HIGHLIGHT);
            int nextLoc = loc + key.length() + BEGIN_HIGHLIGHT.length() + END_HIGHLIGHT.length();
            loc = verse.indexOf(key, nextLoc, Qt::CaseInsensitive);
            ++highlight_count;
        }
    }
    return highlight_count;
}

void Fetcher::_cleanSearchText(QString &request) {
    QMap<QString, QString> replacements({
        {"^\\s*$", ""},  // clear if all whitespace
        {"^\\s*", ""},  // remove all leading whitespace
        {"\\s*$", ""},  // remove all ending whitespace
        {"\\s+", SQL_DELIMITER},  // replace any internal whitespace with single delimiter
    });
    foreach (QString const key, replacements.keys()) {
        request = request.replace(QRegularExpression(key), replacements.value(key));
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
