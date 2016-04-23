#ifndef FETCHER_H
#define FETCHER_H

#include <QObject>
#include <QString>
#include <QtSql>
#include "Defs.h"

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

signals:

public slots:

private:
    QSqlDatabase _db;
};

#endif // FETCHER_H
