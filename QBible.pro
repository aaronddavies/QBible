TEMPLATE = app

QT += qml quick sql
CONFIG += c++11

SOURCES += main.cpp \
    Fetcher.cpp \
    ScriptureModel.cpp \
    SearchModel.cpp

RESOURCES += qml.qrc

HEADERS += \
    Fetcher.h \
    Defs.h \
    ScriptureModel.h \
    SearchModel.h

DISTFILES += \
    bible-sqlite.db \
    bible.db
