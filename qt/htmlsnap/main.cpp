//
//  main.cpp
//  htmlsnap
//
//  Created by Bakken, Jari on 2009-08-22.
//  Copyright 2009 FINN.no AS. All rights reserved.
//
#include <QApplication>
#include "htmlsnap.h"


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    HtmlSnap snap;
    return app.exec();
}
