# -------------------------------------------------
# Project created by QtCreator 2009-08-11T03:43:25
# -------------------------------------------------
QT += network \
    webkit # testlib
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
    lib/qjson/src/parser.h

QMAKE_INFO_PLIST = Info.plist

mac {
    RC_FILE = CelerityViewer.icns
}

QJSON_FAILED=false
# this is obviously the wrong way to do it
unix {
    !exists(lib/libqjson.a) {
        system(mkdir lib/qjson/build)
        system(cd lib/qjson/build && cmake .. && make && ar rcs ../../libqjson.a src/CMakeFiles/qjson.dir/*.o):QJSON_FAILED=TRUE
        system(rm -r lib/qjson/build)
    }
}

win32 {
    !exists(lib\libqjson.dll.a) {
        system(mkdir lib\qjson\build)
        system(cd lib\qjson\build && cmake -G "MinGW Makefiles" .. & mingw32-make.exe && ar rcs ..\..\libqjson.a src\CMakeFiles\qjson.dir\*.o):QJSON_FAILED=TRUE
        system(rd /S lib\qjson\build)
    }
}
    
QJSON_FAILED { error("could not build qjson") }


LIBS += -Llib -lqjson
LIBS -= -mthreads

# win32 {
#     LIBS += -Llib -lqjson-win32
# }

