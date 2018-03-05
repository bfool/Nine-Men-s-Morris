#include "white_win.h"

white_win::white_win(QWidget *parent)
    : QMainWindow(parent)
{
    this->setGeometry(300,60,1000,700);
    this->setMinimumSize(1000,700);
    this->setMaximumSize(1000,700);
    this->setWindowTitle("end");
    //resize(1000,700);
    white_bk=new QLabel(this);
    white_bk->setGeometry(0,0,1000,700);
    white_bk->setScaledContents(1);
    QPixmap win_w;
    win_w.load(":/pic/white_win.jpg");
    white_bk->setPixmap(win_w);
    white_bk->show();

    white_ok=new QLabel (this);
    white_ok->setGeometry(380,330,200,200);
    white_ok->setScaledContents(1);
    QPixmap w_ok;
    w_ok.load(":/pic/ok_button.png");
    white_ok->setPixmap(w_ok);
    white_ok->show();
}

white_win::~white_win()
{

}

void white_win::mousePressEvent(QMouseEvent *e)
{
    if(e->x()>=380&&e->x()<=580&&e->y()>=330&&e->y()<=530)
    {
        this->close();

    }
}
