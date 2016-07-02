#include "SearchModel.h"

SearchModel::SearchModel(Fetcher::Ptr fetcher, QObject *parent) :
    QAbstractListModel(parent),
    _verses(),
    _locations(),
    _scripture(fetcher)
{

}

SearchModel::~SearchModel() {

}

int SearchModel::rowCount(const QModelIndex &parent) const {
    Q_UNUSED(parent)
    return _verses.count();
}

QVariant SearchModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid() || index.row() < 0 || index.row() > _verses.count() - 1) { return QVariant(); }
    if (role == Roles::SCRIPTURE) { return _verses.value(index.row()); }
    if (role == Roles::LOCATION) { return _locations.value(index.row()); }
    return QVariant();
}

QHash<int, QByteArray> SearchModel::roleNames() const {
    return Roles::MAP;
}

void SearchModel::search(const QString request) {
    emit beginResetModel();
    _verses.clear();
    _locations.clear();
    _scripture->search(_verses, _locations, request);
    if (_verses.count() == 0) {
        _verses.append(NO_SEARCH_RESULTS);
    }
    emit endResetModel();
}
