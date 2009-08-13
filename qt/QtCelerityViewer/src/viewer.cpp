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
#include <QPrinter>


namespace celerity {

Viewer::Viewer() : webView(new QWebView())
{
    QWebSettings::globalSettings()->setAttribute(QWebSettings::DeveloperExtrasEnabled, true);

    connect(&server, SIGNAL(jsonReceived(QByteArray)), this, SLOT(processJson(QByteArray)));

    server.run();

    webView->setHtml("<p style=\"font-size: 12px\">Loading QtCelerityViewer...</pre>");
    webView->show();
    webView->load(QUrl("http://celerity.rubyforge.org"));
}

Viewer::~Viewer()
{
    server.stop();
    delete webView;
}

void Viewer::processJson(QByteArray json)
{
    QVariantMap req = parser.parse(json).toMap();

    QString meth = req["method"].toString();
    QString html = req["html"].toString();

    if(meth == "page_changed" && html != lastHtml) {
        lastHtml = html;
        qDebug() << "updating page: " << html.size();
        renderHtml(html, QUrl(req["url"].toString()) );
    }
    else if(meth == "save") {
        save( req["path"].toString() );
    }
}

void Viewer::renderHtml(QString html, QUrl baseUrl)
{
    webView->setHtml(html, baseUrl);
}

void Viewer::save(QString path)
{
    qDebug() << "saving to: " << path;
    QPrinter pdfPrinter(QPrinter::HighResolution);

    pdfPrinter.setFullPage(true);
    pdfPrinter.setPaperSize(QPrinter::B0);
    pdfPrinter.setOutputFileName(path);
    pdfPrinter.setOutputFormat(QPrinter::PdfFormat);

    // TODO: fix frames
    webView->print(&pdfPrinter);
}

} // namespace celerity

