#include "tcpserver.h"
#include <QDebug>

TcpServer::TcpServer(QObject *parent) :
    QTcpServer(parent)
{
}
bool TcpServer::createListen(const QString &ip, unsigned short port)
{
    qDebug()<<"qwertyui createListen";

    QHostAddress addr;
    if(!addr.setAddress(ip))
        return false;
    listen(addr, port);
}
void TcpServer::incomingConnection(int sockFd)
{
    qDebug()<<"incomingConnection";
    QTcpSocket *sock = new QTcpSocket;
    sock->setSocketDescriptor(sockFd);
    emit connectionConnected(sock);
}
