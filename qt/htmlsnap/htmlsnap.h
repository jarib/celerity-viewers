#ifndef HTMLSNAP_H
#define HTMLSNAP_H

#include <QObject>
#include <QWebPage>
#include "server.h"

class HtmlSnap : public QObject
{

    Q_OBJECT

    QWebPage page;
    celerity::Server server;
public:
    HtmlSnap(bool javascriptEnabled);
    void loadHtml(QString html);

private slots:
    void render();
    void processMessage(QVariantMap message);

signals:
    void finished();

};

#endif // HTMLSNAP_H
