#include "ScriptureModel.h"

ScriptureModel::ScriptureModel(Fetcher::Ptr fetcher, QObject *parent) :
    QAbstractListModel(parent),
    _chapter(),
    _scripture(fetcher)
{
    _scripture->fetchChapter(_chapter, DEFAULT_BOOK, DEFAULT_CHAPTER);
}

ScriptureModel::~ScriptureModel() {

}

int ScriptureModel::rowCount(const QModelIndex &parent) const {
    return _chapter.count();
}

QVariant ScriptureModel::data(const QModelIndex &index, int role) const {
    return QVariant();
}
