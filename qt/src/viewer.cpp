//
//  viewer.cpp
//  QtCelerityViewer
//
//  Created by Jari Bakken on 2009-08-13.
//  Copyright 2009 Jari Bakken. All rights reserved.
//


#include "viewer.h"
#include <QWebSettings>
#include <QWebFrame>
#include <QVariantMap>
#include <QPainter>
#include <QFile>

#include <QApplication>
#include <QDesktopWidget>

namespace celerity {

Viewer::Viewer()
{
    connect(&server, SIGNAL(jsonReceived(QByteArray)), this, SLOT(processJson(QByteArray)));
    server.run();
}

Viewer::~Viewer()
{
    server.stop();
}

void Viewer::setWebView(QWebView* view)
{
    webView = view;
    // webView->settings()->setAttribute(QWebSettings::PrintElementBackgrounds, true); /* only works on 4.5 */
    webView->settings()->setAttribute(QWebSettings::DeveloperExtrasEnabled, true);
}

void Viewer::processJson(QByteArray json)
{
    QVariantMap req = parser.parse(json).toMap();

    QString meth = req["method"].toString();
    QString html = req["html"].toString();

    if(meth == "page_changed" && html != lastHtml) {
        lastHtml = html;
        qDebug() << "updating page, html is " << html.size() << " bytes";
        renderHtml(html, QUrl(req["url"].toString()) );
    } else if(meth == "save") {
        save( req["path"].toString() );
    } else if(meth == "save_render_tree") {
        saveRenderTree( req["path"].toString() );
    }
}

void Viewer::renderHtml(QString html, QUrl baseUrl)
{
    emit urlChanged(baseUrl.toString());
    webView->setHtml(html, baseUrl);
}

void Viewer::save(QString path)
{
    if(path.isNull() || path.isEmpty()) {
        return;
    }

    qDebug() << "saving to: " << path;
    QWebPage *page   = webView->page();
    QWebFrame *frame = page->currentFrame();
    QSize origSize   = page->viewportSize();

    page->setViewportSize(frame->contentsSize());
    QImage image(page->viewportSize(), QImage::Format_ARGB32);
    QPainter painter(&image);
    frame->render(&painter);
    page->setViewportSize(origSize);
    painter.end();

    if(!path.endsWith(".png"))
        path += ".png";

    image.save(path);
}

void Viewer::saveScreenshot(QString path)
{
    if(path.isNull() || path.isEmpty())
        return;

    QPixmap pixmap = QPixmap::grabWindow(QApplication::desktop()->winId());
    pixmap.save(path, "png");
}

void Viewer::saveRenderTree(QString path)
{
    if(path.isNull() || path.isEmpty())
        return;


    QFile file(path);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
      qDebug() << "Failed to open '" << path << "' in saveRenderTree().";
      return;
    }

    file.write(webView->page()->mainFrame()->renderTreeDump().toUtf8());
    file.close();
}

} // namespace celerity

