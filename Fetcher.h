#ifndef FETCHER_H
#define FETCHER_H

#include <QObject>
#include <QString>
#include <QtSql>
#include "Defs.h"

QStringList const BAD = {"{.*}", "\\\\", "&gt; "};
QString const EMPTY = "";

/**
 * @brief The Fetcher class
 * Provides an interface to the scripture database.
 */
class Fetcher : public QObject
{
    Q_OBJECT
public:
    typedef QSharedPointer<Fetcher> Ptr;

    explicit Fetcher(QObject *parent = 0);
    virtual ~Fetcher();

    /**
     * @brief fetchChapter - Fetches a single chapter from a book.
     * @param book
     * @param chapter
     */
    void fetchChapter(QStringList &result, int const book, int const chapter);

    /**
     * @brief fetchTitle - Fetches the title of a book.
     * @param result
     * @param book
     */
    QString fetchTitle(int const book);

    /**
     * @brief chapterCount
     * @return
     */
    int chapterCount(int const book);

    /**
     * @brief search - Finds verses and their locations that contain the requested text.
     * The search is an AND on each word in the order they appear in the string,
     *   allowing other text in between.
     * @param request
     * @return
     */
    void search(QStringList &verses, QStringList &locations, QString const request);

private:
    /**
     * @brief convertText - Clean up the text in the query and fill up the string list.
     * @param query
     * @param result
     */
    void _convertText(QSqlQuery query, int const column, QStringList &result);

    /**
     * @brief _locations - Provides the chapter and verse locations of each verse in the query.
     * @param query
     * @param result
     */
    void _locations(QSqlQuery query, QStringList &result);

    QSqlDatabase _db;
};

#endif // FETCHER_H
