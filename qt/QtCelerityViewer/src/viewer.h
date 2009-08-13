//
//  viewer.h
//  QtCelerityViewer
//
//  Created by Jari Bakken on 2009-08-13.
//  Copyright 2009 Jari Bakken. All rights reserved.
//

#ifndef VIEWER_H
#define VIEWER_H

#include <QWebView>
#include "lib/qjson/src/parser.h" // FIXME
#include "server.h"

namespace celerity {
    class Viewer : public QObject {
        Q_OBJECT

        QWebView* webView;
        Server server;
        QJson::Parser parser;
        QString lastHtml;

    public:
        Viewer();
        ~Viewer();

     public slots:
        void processJson(QByteArray json);
        void renderHtml(QString, QUrl baseUrl = QUrl());
        void save(const QString path);

    protected:
        void saveRenderTree(QString path);

    };
}

#endif // VIEWER_H
