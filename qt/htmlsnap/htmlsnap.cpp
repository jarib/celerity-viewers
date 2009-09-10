#include "htmlsnap.h"
#include <QPainter>
#include <QDebug>
#include <QWebFrame>
#include <QTimer>
#include <iostream>
#include <QBuffer>
#include <QVariantMap>

HtmlSnap::HtmlSnap(bool javascriptEnabled)
{
    QWebSettings::globalSettings()->setAttribute(QWebSettings::JavascriptEnabled, javascriptEnabled);

    connect(&page, SIGNAL(loadFinished(bool)), this, SLOT(render()));
    connect(&server, SIGNAL(messageReceived(QVariantMap)), this, SLOT(processMessage(QVariantMap)));

    server.run();
}

void HtmlSnap::loadHtml(QString html)
{
    page.mainFrame()->setHtml(html, QUrl());
}

void HtmlSnap::processMessage(QVariantMap message)
{
    if(message.contains("width") && message.contains("height")) {
        int width, height;
        bool widthOk, heightOk;

        width  = message["width"].toInt(&widthOk);
        height = message["height"].toInt(&heightOk);

        if(widthOk && heightOk){
            userSize.setHeight(height);
            userSize.setWidth(width);
        } else {
            qDebug() << "invalid parameters! :width => " << message["width"] << ", :height => " << message["height"];
        }
    }

    loadHtml(message["html"].toString());
}

void HtmlSnap::render()
{
    if(userSize.isEmpty()) {
        page.setViewportSize(page.mainFrame()->contentsSize());
    } else {
        page.setViewportSize(userSize);
    }

    QImage image(page.viewportSize(), QImage::Format_ARGB32);
    QPainter painter(&image);

    page.mainFrame()->render(&painter);
    painter.end();

    QByteArray data;
    QBuffer buffer(&data);
    buffer.open(QBuffer::WriteOnly);

    if(!image.save(&buffer, "PNG"))
        std::cerr << "could not save data to buffer";
    else
    {
        QVariantMap message;
        message.insert("image", QString(data.toBase64()));
        server.send(message);
    }

    userSize.setHeight(0);
    userSize.setWidth(0);

    emit finished();
}
