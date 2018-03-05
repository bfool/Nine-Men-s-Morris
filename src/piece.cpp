#include "piece.h"

piece::piece(QWidget *parent)
    : QMainWindow(parent)
{
    this->setGeometry(300,60,1000,700);
    this->setMinimumSize(1000,700);
    this->setMaximumSize(1000,700);
    this->setWindowTitle("end");
    //resize(1000,700);
    piece_bk=new QLabel(this);
    piece_bk->setGeometry(0,0,1000,700);
    piece_bk->setScaledContents(1);
    QPixmap pb;
    pb.load(":/pic/piece.jpg");
    piece_bk->setPixmap(pb);
    piece_bk->show();

    piece_or_not=new QLabel (this);
    piece_or_not->setGeometry(380,330,200,200);
    piece_or_not->setScaledContents(1);
    QPixmap p_ok;
    p_ok.load(":/pic/ok_button.png");
    piece_or_not->setPixmap(p_ok);
    piece_or_not->show();

}

piece::~piece()
{

}

void piece::mousePressEvent(QMouseEvent *e)
{
    if(e->x()>=380&&e->x()<=580&&e->y()>=330&&e->y()<=530)
    {
        this->close();

    }
}
