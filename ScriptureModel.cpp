#include "ScriptureModel.h"

ScriptureModel::ScriptureModel(Fetcher::Ptr fetcher, QObject *parent) :
    QAbstractListModel(parent),
    _chapter(),
    _chapterCount(),
    _scripture(fetcher)
{
    _scripture->fetchChapter(_chapter, DEFAULT_BOOK, DEFAULT_CHAPTER);
    _chapterCount = _scripture->chapterCount(DEFAULT_BOOK);
}

ScriptureModel::~ScriptureModel() {

}

int ScriptureModel::rowCount(const QModelIndex &parent) const {
    Q_UNUSED(parent)
    return _chapter.count();
}

QVariant ScriptureModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid() || index.row() < 0 || index.row() > _chapter.count() - 1) { return QVariant(); }
    if (role == Roles::SCRIPTURE) { return _chapter.value(index.row()); }
    if (role == Roles::VERSE) { return index.row() + 1; }
    return QVariant();
}

QHash<int, QByteArray> ScriptureModel::roleNames() const {
    return Roles::MAP;
}

void ScriptureModel::fetch(const int book, const int chapter) {
    emit beginRemoveRows(QModelIndex(), 0, _chapter.count() - 1);
    _chapter.clear();
    emit endRemoveRows();
    QStringList newChapter;
    _scripture->fetchChapter(newChapter, book, chapter);
    _chapterCount = _scripture->chapterCount(book);
    emit beginInsertRows(QModelIndex(), 0, newChapter.count() - 1);
    _chapter = newChapter;
    emit endInsertRows();
}

int ScriptureModel::chapterCount() {
    return _chapterCount;
}

QString ScriptureModel::bookTitle(const int book) {
    return _scripture->fetchTitle(book);
}
