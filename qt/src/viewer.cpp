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
#include <QPainter>
#include <QFile>
#include <QBuffer>

#include <QApplication>
#include <QDesktopWidget>

namespace celerity {

Viewer::Viewer()
{
    connect(&server, SIGNAL(messageReceived(QVariantMap)), this, SLOT(processMessage(QVariantMap)));
    server.run();
}

Viewer::~Viewer()
{
    server.stop();
}

void Viewer::setWebView(QWebView* view)
{
    webView = view;
    webView->settings()->setAttribute(QWebSettings::DeveloperExtrasEnabled, true);
}

void Viewer::processMessage(QVariantMap req)
{
    QString meth = req["method"].toString();
    QString html = req["html"].toString();

    if(meth == "page_changed" && html != lastHtml) {
        lastHtml = html;
        qDebug() << "updating page, html is " << html.size() << " bytes";
        renderHtml(html, req["url"].toString() );
    } else if(meth == "save")
        save(req["path"].toString());
      else if(meth == "image_data")
        sendImageData();
      else if(meth == "render_tree")
        sendRenderTree();
      else if(meth == "save_render_tree")
        saveRenderTree(req["path"].toString());
}

void Viewer::renderHtml(QString html, QString url)
{
    emit urlChanged(url);
    QUrl fullUrl(url);
    webView->setHtml(html, QUrl(fullUrl.toString(QUrl::RemovePath)));
}

void Viewer::save(QString path)
{
    if(path.isNull() || path.isEmpty())
        return;

    if(!path.endsWith(".png"))
        path += ".png";

    qDebug() << "saving to: " << path;

    QImage image(webView->page()->currentFrame()->contentsSize(), QImage::Format_ARGB32);
    renderPageTo(&image);
    image.save(path);
}

void Viewer::sendImageData()
{
    QImage image(webView->page()->currentFrame()->contentsSize(), QImage::Format_ARGB32);
    renderPageTo(&image);

    QByteArray data;
    QBuffer buffer(&data);
    buffer.open(QBuffer::WriteOnly);

    QVariantMap message;

    if(!image.save(&buffer, "PNG"))
        message.insert("error", "could not save image data to buffer");
    else {
        message.insert("image", QString(data.toBase64()));
    }

    server.send(message);
}

void Viewer::saveScreenshot(QString path)
{
    if(path.isNull() || path.isEmpty())
        return;

    QPixmap pixmap = QPixmap::grabWindow(QApplication::desktop()->winId());
    pixmap.save(path, "png");
}

void Viewer::renderPageTo(QImage* image)
{
    QWebPage *page   = webView->page();
    QWebFrame *frame = page->currentFrame();
    QSize origSize   = page->viewportSize();

    page->setViewportSize(frame->contentsSize());

    QPainter painter(image);
    frame->render(&painter);

    painter.end();
    page->setViewportSize(origSize);
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

void Viewer::sendRenderTree()
{
    QVariantMap message;
    message.insert("render_tree", webView->page()->mainFrame()->renderTreeDump());
    server.send(message);
}


} // namespace celerity

