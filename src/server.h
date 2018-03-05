#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QTcpSocket>
#include <QTcpServer>

class TcpServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit TcpServer(QObject *parent = 0);
    bool createListen(const QString &ip, unsigned short port);
protected:
    void incomingConnection(int sockFd);
signals:
    void connectionConnected(QTcpSocket *socket);


public slots:

};

#endif // TCPSERVER_H
