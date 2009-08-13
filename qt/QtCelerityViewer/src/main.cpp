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

    celerity::Viewer* viewer = new celerity::Viewer();


    int result = a.exec();
    delete viewer;
    return result;
}
