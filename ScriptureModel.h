#ifndef SCRIPTUREMODEL_H
#define SCRIPTUREMODEL_H

#include <QObject>
#include <QAbstractListModel>
#include "Fetcher.h"

namespace Roles {

enum {
    SCRIPTURE = 0,
    VERSE = 1,
    CHAPTER = 2,
    BOOK = 3
};

QHash<int, QByteArray> const MAP({
    {SCRIPTURE, "scripture"}, {VERSE, "verse"}, {CHAPTER, "chapter"}, {BOOK, "book"}
});

}

/**
 * @brief The ScriptureModel class
 * This is a ListModel for viewing a single chapter.
 */
class ScriptureModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit ScriptureModel(Fetcher::Ptr fetcher, QObject *parent = 0);
    virtual ~ScriptureModel();

    Q_INVOKABLE int rowCount(const QModelIndex &parent = QModelIndex()) const;
    Q_INVOKABLE QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    Q_INVOKABLE QHash<int, QByteArray> roleNames() const;

    Q_INVOKABLE void fetch(int const book, int const chapter);
    Q_INVOKABLE int chapterCount();
    Q_INVOKABLE QString bookTitle(int const book);

signals:
    void fadeOut();
    void fadeIn();

private:
    QStringList _chapter;
    int _chapterCount;
    Fetcher::Ptr _scripture;
};

#endif // SCRIPTUREMODEL_H
