//
//  main.cpp
//  QtCelerityViewer
//
//  Created by Jari Bakken on 2009-08-13.
//  Copyright 2009 Jari Bakken. All rights reserved.
//


#include <QtGui/QApplication>
#include "mainwindow.h"
#include "viewer.h"
#include "server.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    MainWindow w;

    celerity::Viewer* viewer = new celerity::Viewer();
    viewer->setWebView(w.view);
    w.connect(viewer, SIGNAL(urlChanged(QString)), SLOT(setLocation(QString)));

    w.show();

//    int result = a.exec();
//    delete viewer;
//    return result;
    return a.exec();
}
