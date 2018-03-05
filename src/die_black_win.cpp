#include "die_black_win.h"

die_black_win::die_black_win(QWidget *parent)
    : QMainWindow(parent)
{
   this->setGeometry(300,60,800,600);
    //resize(800,600);
    this->setMinimumSize(800,600);
    this->setMaximumSize(800,600);
    this->setWindowTitle("end");
    die_bk=new QLabel(this);
    die_bk->setGeometry(0,0,800,600);
    die_bk->setScaledContents(1);
    QPixmap d_win_b;
    d_win_b.load(":/pic/die_black_win.jpg");
    die_bk->setPixmap(d_win_b);
    die_bk->show();

    die_bk_ok=new QLabel (this);
    die_bk_ok->setGeometry(380,330,150,150);
    die_bk_ok->setScaledContents(1);
    QPixmap d_b_ok;
    d_b_ok.load(":/pic/ok_button.png");
    die_bk_ok->setPixmap(d_b_ok);
    die_bk_ok->show();
}
die_black_win::~die_black_win()
{

}

void die_black_win::mousePressEvent(QMouseEvent *e)
{
    if(e->x()>=380&&e->x()<=530&&e->y()>=330&&e->y()<=480)
    {
        this->close();
    }
}
