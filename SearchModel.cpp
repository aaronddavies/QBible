#include "SearchModel.h"

SearchModel::SearchModel(Fetcher::Ptr fetcher, QObject *parent) :
    QAbstractListModel(parent),
    _results(),
    _scripture(fetcher)
{

}

SearchModel::~SearchModel() {

}

int SearchModel::rowCount(const QModelIndex &parent) const {
    Q_UNUSED(parent)
    return _results.count();
}

QVariant SearchModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid() || index.row() < 0 || index.row() > _results.count() - 1) { return QVariant(); }
    if (role == Roles::SCRIPTURE) { return _results.at(index.row()).text; }
    if (role == Roles::LOCATION) { return _results.at(index.row()).location; }
    return QVariant();
}

QHash<int, QByteArray> SearchModel::roleNames() const {
    return Roles::MAP;
}

void SearchModel::search(const QString request) {
    emit beginResetModel();
    _results.clear();
    _scripture->search(_results, request);
    if (_results.count() == 0) {
        FetchedVerse none;
        none.text = NO_SEARCH_RESULTS;
        none.chapter = DEFAULT_CHAPTER;
        none.book = DEFAULT_BOOK;
        _results.push_back(none);
    }
    emit endResetModel();
}

int SearchModel::bookAt(const int row) const {
    return _results.at(row).book;
}

int SearchModel::chapterAt(const int row) const {
    return _results.at(row).chapter;
}
