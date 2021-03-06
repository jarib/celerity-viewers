# -------------------------------------------------
# Project created by QtCreator 2009-08-11T03:43:25
# -------------------------------------------------
QT += network webkit # testlib
TARGET = QtCelerityViewer
TEMPLATE = app
INCLUDEPATH += lib/qjson/src
SOURCES += src/main.cpp \
    src/mainwindow.cpp \
    src/viewer.cpp \
    src/server.cpp
HEADERS += src/mainwindow.h \
    src/viewer.h \
    src/server.h \
    lib/qjson/src/parser.h \
    lib/qjson/src/serializer.h

QMAKE_INFO_PLIST = Info.plist

# icons
mac { RC_FILE = CelerityViewer-mac.icns }
win32 { RC_FILE = icon-win32.rc }

unix {
    !exists(lib/libqjson.a) {
        # this == ugly? suggestions welcome :)
        system(mkdir lib/qjson/build)
        system(cd lib/qjson/build && cmake .. && make && ar rcs ../../libqjson.a src/CMakeFiles/qjson.dir/*.o)
        system(rm -r lib/qjson/build)
    }

    LIBS += -Llib -lqjson
}

win32 {
    !exists(lib/libqjson-win32.dll) {
        error("expected lib/libqjson-win32.dll to already exist")
    }

    LIBS += -Llib -lqjson-win32
}



