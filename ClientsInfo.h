#ifndef CLIENTSINFO_H
#define CLIENTSINFO_H

#include <QObject>
#include <QTcpSocket>
#include <QMap>
#include <QString>
#include <QPair>
#include "Def.h"

#if MYDEBUG
typedef QMap<QString, QTcpSocket*>::iterator ClientInfo;
#else
typedef QMap<int, QTcpSocket*>::iterator ClientInfo;
#endif
class ClientsInfo : public QObject
{
    Q_OBJECT
public:
    explicit ClientsInfo(QObject *parent = 0);
#if MYDEBUG
    void addClient(QString clientIP, QTcpSocket *tcpSock);
    bool hasClient(QString clientIP);
    ClientInfo findClient(QString clientIP);
#else
    void addClient(int clientPort, QTcpSocket *tcpSock);
    bool hasClient(int clientPort);
    ClientInfo findClient(int clientPort);
#endif
signals:

public slots:

public:
#if MYDEBUG
    QMap<QString, QTcpSocket*> mClientsInfo;
#else
    QMap<int, QTcpSocket*> mClientsInfo;
#endif
};

#endif // CLIENTSINFO_H
