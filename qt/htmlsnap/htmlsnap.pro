# -------------------------------------------------
# Project created by QtCreator 2009-08-11T03:43:25
# -------------------------------------------------
QT += network webkit
TARGET = htmlsnap
CONFIG += console
CONFIG -= app_bundle
TEMPLATE = app
INCLUDEPATH += ../lib/qjson/src ../src
SOURCES += main.cpp ../src/server.cpp htmlsnap.cpp
HEADERS += ../src/server.h htmlsnap.h ../lib/qjson/src/parser.h ../lib/qjson/src/serializer.h

LIBS += -L../lib -lqjson


