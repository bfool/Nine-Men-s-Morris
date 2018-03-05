#include "mainwindow.h"
#include "game_window.h"
#include "flash2.h"
#include <QApplication>
#include "logindilog.h"
#include "online.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

   // online w;
   // logindilog ld;
    //ld.show();




   // QObject::connect(&ld, SIGNAL(connected(QTcpSocket*,bool)),&w, SLOT(startGame(QTcpSocket*,bool)));
    flash2 f;
    f.show();

    return a.exec();
}
