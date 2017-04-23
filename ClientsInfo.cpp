#include "ClientsInfo.h"

ClientsInfo::ClientsInfo(QObject *parent) :
    QObject(parent)
{
}
#if MYDEBUG
void ClientsInfo::addClient(QString clientIP, QTcpSocket *tcpSock)
{
    if(!hasClient(clientIP)){
        mClientsInfo.insert(clientIP, tcpSock);
    }
}
#else
void ClientsInfo::addClient(int clientPort, QTcpSocket *tcpSock)
{
    if(!hasClient(clientPort)){
        mClientsInfo.insert(clientPort, tcpSock);
    }
}
#endif

#if MYDEBUG
bool ClientsInfo::hasClient(QString clientIP)
{
    return mClientsInfo.contains(clientIP);
}
#else
bool ClientsInfo::hasClient(int clientPort)
{
    return mClientsInfo.contains(clientPort);
}
#endif
#if MYDEBUG
ClientInfo ClientsInfo::findClient(QString clientIP)
{
    return mClientsInfo.find(clientIP);
}
#else
ClientInfo ClientsInfo::findClient(int clientPort)
{
    return mClientsInfo.find(clientPort);
}
#endif
