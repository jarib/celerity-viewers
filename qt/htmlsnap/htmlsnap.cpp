#include "htmlsnap.h"
#include <QPainter>
#include <QDebug>
#include <QWebFrame>
#include <QTimer>
#include <iostream>
#include <QBuffer>
#include <QVariantMap>

HtmlSnap::HtmlSnap()
{
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
    loadHtml(message["html"].toString());
}


void HtmlSnap::render()
{
    page.setViewportSize(page.mainFrame()->contentsSize());
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

    emit finished();
}
