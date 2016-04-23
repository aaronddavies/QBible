#ifndef SCRIPTUREMODEL_H
#define SCRIPTUREMODEL_H

#include <QObject>
#include <QAbstractListModel>
#include "Fetcher.h"

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

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

private:
    QStringList _chapter;
    Fetcher::Ptr _scripture;
};

#endif // SCRIPTUREMODEL_H
