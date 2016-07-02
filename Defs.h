#ifndef DEFS_H
#define DEFS_H

#include <QDebug>

static int constexpr DEFAULT_BOOK = 1;
static int constexpr DEFAULT_CHAPTER = 1;

QString const BEGIN_HIGHLIGHT = "<b>";
QString const END_HIGHLIGHT = "</b>";
QString const NO_SEARCH_RESULTS = "<i>No results.</i>";
static char constexpr DELIMITER = ' ';

namespace Roles {

enum {
    SCRIPTURE = 0,
    VERSE = 1,
    LOCATION = 2,
};

QHash<int, QByteArray> const MAP({
    {SCRIPTURE, "scripture"}, {VERSE, "verse"}, {LOCATION, "location"}
});

}

#endif // DEFS_H
