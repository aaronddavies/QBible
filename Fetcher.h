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
     * @brief convertText - Cleans up the text from the query.
     * @param query
     * @param result
     */
    QString _convertText(QVariant const value);

    /**
     * @brief _locations - Provides a formatted display string of the chapter and verse.
     * @param query
     * @param result
     */
    QString _locationDisplay(QVariant const book, QVariant const chapter, QVariant const verse);

    QSqlDatabase _db;
};

#endif // FETCHER_H
