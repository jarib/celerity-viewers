# -------------------------------------------------
# Project created by QtCreator 2009-08-11T03:43:25
# -------------------------------------------------
QT += network webkit # testlib
TARGET = QtCelerityViewer
TEMPLATE = app
RC_FILE = CelerityViewer.icns

SOURCES +=  src/main.cpp \
            src/mainwindow.cpp \
            src/viewer.cpp \
            src/server.cpp

HEADERS += src/mainwindow.h \
           src/viewer.h \
           src/server.h \
           lib/qjson/src/parser.h

LIBS +=  -Llib/qjson/build/lib -lqjson

QMAKE_INFO_PLIST = Info.plist
