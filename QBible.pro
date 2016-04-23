TEMPLATE = app

QT += qml quick sql
CONFIG += c++11

SOURCES += main.cpp \
    Fetcher.cpp \
    ScriptureModel.cpp

RESOURCES += qml.qrc

HEADERS += \
    Fetcher.h \
    Defs.h \
    ScriptureModel.h

DISTFILES += \
    bible-sqlite.db
