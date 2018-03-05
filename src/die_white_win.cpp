#include "die_white_win.h"

die_white_win::die_white_win(QWidget *parent)
    : QMainWindow(parent)
{
    this->setGeometry(300,60,800,600);
    //resize(800,600);
    this->setMinimumSize(800,600);
    this->setMaximumSize(800,600);
    this->setWindowTitle("end");
    die_wk=new QLabel(this);
    die_wk->setGeometry(0,0,800,600);
    die_wk->setScaledContents(1);
    QPixmap d_win_w;
    d_win_w.load(":/pic/die_white_win.jpg");
    die_wk->setPixmap(d_win_w);
    die_wk->show();

    die_wk_ok=new QLabel (this);
    die_wk_ok->setGeometry(380,330,150,150);
    die_wk_ok->setScaledContents(1);
    QPixmap d_w_ok;
    d_w_ok.load(":/pic/ok_button.png");
    die_wk_ok->setPixmap(d_w_ok);
    die_wk_ok->show();
}
die_white_win::~die_white_win()
{

}

void die_white_win::mousePressEvent(QMouseEvent *e)
{
    if(e->x()>=380&&e->x()<=530&&e->y()>=330&&e->y()<=480)
    {
        this->close();
    }
}
