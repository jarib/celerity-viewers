//
//  server.h
//  QtCelerityViewer
//
//  Created by Jari Bakken on 2009-08-13.
//  Copyright 2009 Jari Bakken. All rights reserved.
//


#ifndef SERVER_H
#define SERVER_H

#include <QThread>
#include <QTcpServer>
#include <QRegExp>
#include <QMutex>
#include <QVariantMap>

#include "serializer.h"
#include "parser.h"

namespace celerity {
    class Server : public QObject {

        Q_OBJECT

        QTcpServer* tcpServer;
        QTcpSocket* socket;
        QMutex mutex;
        QByteArray jsonString;
        int length, bytesRead;

        QJson::Serializer serializer;
        QJson::Parser parser;

    public:
        Server(QObject* parent = 0);
        ~Server();
        void run();
        void stop();
        void send(QVariantMap data);

    signals:
        void messageReceived(QVariantMap message);

    public slots:
        void acceptConnection();
        void readSocket();
        void closeSocket();

    protected:
        int readNextMessageLength();

    };
}

#endif // SERVER_H
