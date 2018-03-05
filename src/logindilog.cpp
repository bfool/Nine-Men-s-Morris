#include "logindilog.h"
#include "ui_logindilog.h"

logindilog::logindilog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::logindilog)
{
    qDebug()<<"login";
    ui->setupUi(this);
    server=0;
    socket=0;
    timer=new QTimer(this);
    connect(timer, SIGNAL(timeout()),this, SLOT(timeout()));
}

logindilog::~logindilog()
{
    delete ui;
}
void logindilog::clientConnected()
{
    emit connected(socket, false);
    accept();

}
void logindilog::serverConnected(QTcpSocket *s)
{
    emit connected(s, true);
    accept();
}


void logindilog::on_startBtn_clicked()
{
    qDebug()<<"xuanze";
    unsigned short port=ui->portEdit->text().toInt();
    if(ui->radioButtonClient->isChecked())
    {
        QHostAddress addr;
        addr.setAddress(ui->ipEdit->text());
        socket=new QTcpSocket;
        connect(socket, SIGNAL(connected()), this,SLOT(clientConnected()));
        socket->connectToHost(addr, port);
    }
    else{
        server = new TcpServer(this);
        connect(server, SIGNAL(connectionConnected(QTcpSocket*)),
                this, SLOT(serverConnected(QTcpSocket*)));
        server->createListen(ui->ipEdit->text(),port);
    }
    timer->start(30);
}
void logindilog::timeout()
{
    ui->progressBar->setValue(
            (ui->progressBar->value() + 1) % 101);
}

void logindilog::on_quitBtn_clicked()
{
    exit(0);
}
