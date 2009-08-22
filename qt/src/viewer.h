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
#include <QVariantMap>
#include "server.h"

namespace celerity {
    class Viewer : public QObject {
        Q_OBJECT

        QWebView* webView;
        Server server;
        QString lastHtml;

    public:
        Viewer();
        ~Viewer();

        void setWebView(QWebView* webView);

    signals:
        void urlChanged(QString newUrl);

     public slots:
        void processMessage(QVariantMap req);
        void renderHtml(QString, QString url = QString());
        void save(const QString path);
        void saveScreenshot(const QString path);

    protected:
        void saveRenderTree(QString path);
        void renderPageTo(QImage *image);
        void sendImageData();
        void sendRenderTree();

    };
}

#endif // VIEWER_H
