//
//  server.cpp
//  QtCelerityViewer
//
//  Created by Jari Bakken on 2009-08-13.
//  Copyright 2009 Jari Bakken. All rights reserved.
//


#include <QVariantMap>
#include <QTcpSocket>
#include "server.h"

#define GETENV(var, def) (getenv(var) != 0 ? QString(getenv(var)) : QString(def))

namespace celerity {

Server::Server(QObject *parent)
    : QObject(parent)
    , socket(0)
    , jsonString("")
    , length(0)
    , bytesRead(0)
{
    qDebug() << "creating Server";
    return;
}

Server::~Server()
{
    qDebug() << "destroying Server";
    delete tcpServer;
}

void Server::run()
{
    QString host = GETENV("QT_CELERITY_VIEWER_HOST", "0.0.0.0");
    int     port = GETENV("QT_CELERITY_VIEWER_PORT", "6429").toInt();

    tcpServer = new QTcpServer();
    tcpServer->listen(QHostAddress(host), port);

    connect(tcpServer, SIGNAL(newConnection()), this, SLOT(acceptConnection()));

    qDebug() << "Server started on host: " << host << " port: " << port;
}

void Server::stop()
{
    closeSocket();
    tcpServer->close();
}

void Server::acceptConnection()
{
    qDebug() << "client connecting...";

    // we only allow one connection at a time
    if(socket) {
        qDebug() << "deleting old socket";
        closeSocket();
        delete socket;
    }

    socket = tcpServer->nextPendingConnection();

    if(!socket)
        return;

    connect(socket, SIGNAL(readyRead()), this, SLOT(readSocket()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(closeSocket()));
    qDebug() << "ok.";
}

void Server::readSocket()
{
    int available = socket->bytesAvailable();
    while(available > 0) {
         QByteArray buf = socket->read(16);
         if(buf == "Content-Length: ") {
             length = readNextMessageLength();
             jsonString.clear();
             bytesRead = 0;
         } else {
             jsonString.append(buf);
             jsonString.append(socket->read(available));
             bytesRead += available;
         }

         if(bytesRead == length) {
             emit jsonReceived(jsonString);
             jsonString.clear();
             bytesRead = 0;
             length = 0;
         }

         available = socket->bytesAvailable();
    }
}

int Server::readNextMessageLength()
{
    QByteArray buf = "";
    int jsonLength = 0;
    bool ok;

    while(socket->isOpen() && !socket->atEnd() && !buf.endsWith("\n\n"))
        buf.append(socket->read(1));

    if(buf.endsWith("\n\n")) {
        buf.chop(2); // remove \n\n
        jsonLength = buf.toInt(&ok);
    } else
        ok = false;

    if(!ok)
        qDebug() << "error in readNextMessageLength(), buf is: " << buf;

    return jsonLength;
}


void Server::closeSocket()
{
    if(socket) {
        socket->close();
        disconnect(socket, 0, 0, 0);
    }
}

} // namespace celerity
