#ifndef SEARCHMODEL_H
#define SEARCHMODEL_H

#include <QObject>
#include <QAbstractListModel>
#include "Fetcher.h"

/**
 * @brief The SearchModel class
 */
class SearchModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit SearchModel(Fetcher::Ptr fetcher, QObject *parent = 0);
    virtual ~SearchModel();

    Q_INVOKABLE int rowCount(const QModelIndex &parent = QModelIndex()) const;
    Q_INVOKABLE QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    Q_INVOKABLE QHash<int, QByteArray> roleNames() const;

    Q_INVOKABLE void search(QString const request);
    Q_INVOKABLE int bookAt(int const row) const;
    Q_INVOKABLE int chapterAt(int const row) const;

private:
    QVector<FetchedVerse> _results;
    Fetcher::Ptr _scripture;
};

#endif // SEARCHMODEL_H
