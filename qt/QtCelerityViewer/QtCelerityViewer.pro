# -------------------------------------------------
# Project created by QtCreator 2009-08-11T03:43:25
# -------------------------------------------------
QT       += network webkit # testlib
TARGET   = QtCelerityViewer
TEMPLATE = app
RC_FILE  = CelerityViewer.icns

SOURCES +=  src/main.cpp \
            src/mainwindow.cpp \
            src/viewer.cpp \
            src/server.cpp

HEADERS += src/mainwindow.h \
           src/viewer.h \
           src/server.h \
           lib/qjson/src/parser.h

QMAKE_INFO_PLIST = Info.plist

unix {
    !exists(lib/libqjson.a) {
        # help, what's the proper way to do build qjson as a static dependency?
        system(mkdir lib/qjson/build && cd lib/qjson/build && cmake .. && make && ar rcs ../../libqjson.a src/CMakeFiles/qjson.dir/*.o)
        system(rm -r lib/qjson/build)
    }
    
    LIBS       += -Llib/ -lqjson
}

