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

    bool jsEnabled;

    QStringList args = app.arguments();
    if(args.size() > 1 && args.at(1) == "--disable-javascript")
        jsEnabled = false;
    else
        jsEnabled = true;

    qDebug() << "javascript enabled: " << jsEnabled;

    HtmlSnap snap(jsEnabled);
    return app.exec();
}
