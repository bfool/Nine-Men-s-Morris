#ifndef LOGINDILOG_H
#define LOGINDILOG_H

#include <QDialog>
#include <QTcpSocket>
#include <tcpserver.h>
#include <QTimer>

namespace Ui {
    class logindilog;
}

class logindilog : public QDialog
{
    Q_OBJECT

public:
    explicit logindilog(QWidget *parent = 0);
    ~logindilog();
signals:
    void connected(QTcpSocket *socket, bool isServer);

private:
    Ui::logindilog *ui;
    TcpServer *server;
    QTcpSocket *socket;
    QTimer *timer;


private slots:
    void clientConnected();
    void serverConnected(QTcpSocket *);
    void timeout();
    void on_startBtn_clicked();
    void on_quitBtn_clicked();
};

#endif // LOGINDILOG_H
