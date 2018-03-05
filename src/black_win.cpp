#include "black_win.h"

black_win::black_win(QWidget *parent)
    : QMainWindow(parent)
{
    this->setGeometry(300,60,1000,700);
    //resize(1000,700);
    this->setMinimumSize(1000,700);
    this->setMaximumSize(1000,700);
    this->setWindowTitle("black win");
    black_bk=new QLabel(this);
    black_bk->setGeometry(0,0,1000,700);
    black_bk->setScaledContents(1);
    QPixmap win_b;
    win_b.load(":/pic/black_win.jpg");
    black_bk->setPixmap(win_b);
    black_bk->show();

    black_ok=new QLabel (this);
    black_ok->setGeometry(380,330,200,200);
    black_ok->setScaledContents(1);
    QPixmap b_ok;
    b_ok.load(":/pic/ok_button.png");
    black_ok->setPixmap(b_ok);
    black_ok->show();
}
black_win::~black_win()
{

}

void black_win::mousePressEvent(QMouseEvent *e)
{
    if(e->x()>=380&&e->x()<=580&&e->y()>=330&&e->y()<=530)
    {
        this->close();

    }
}

