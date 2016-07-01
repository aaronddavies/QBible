#ifndef DEFS_H
#define DEFS_H

#include <QDebug>

static int constexpr DEFAULT_BOOK = 1;
static int constexpr DEFAULT_CHAPTER = 1;

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
