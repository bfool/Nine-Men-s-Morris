#include "flash2.h"

flash2::flash2(QWidget *parent)
    : QMainWindow(parent)
{
    this->setGeometry(300,150,1024,545);
    //resize(1024,545);
    this->setWindowFlags(this->windowFlags()&~Qt::WindowMaximizeButtonHint);
    this->setWindowTitle("welcome");
    this->setMinimumSize(1024,545);
    this->setMaximumSize(1024,545);
    main_map=new QLabel(this);
    main_map->setGeometry(0,0,1024,545);
    QPixmap bb;
    bb.load(":/pic/flash.jpg");
    main_map->setScaledContents(1);
    main_map->setPixmap(bb);
    main_map->show();

    connect(this,SIGNAL(clicked()),this,SLOT(enter_game()));
}
flash2::~flash2()
{

}

void flash2::mousePressEvent(QMouseEvent *e)
{

    if(e->x()>=0&&e->x()<=1024&&e->y()>=0&&e->y()<=545);

    emit clicked();
}

void flash2::enter_game()
{
    this->hide();
    w.show();
}
