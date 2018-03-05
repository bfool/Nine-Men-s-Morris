#include "warm_tip.h"

warm_tip::warm_tip(QWidget *parent)
    : QMainWindow(parent)
{
    this->setGeometry(410,105,800,700);
    this->setMinimumSize(800,700);
    this->setMaximumSize(800,700);
    this->setWindowTitle("tip");
    //resize(800,700);
    w_rule=new QLabel(this);
    QPixmap w_r;
    w_r.load(":/pic/main_tips.jpg");
    w_rule->setGeometry(0,0,800,700);
    w_rule->setScaledContents(1);
    w_rule->setPixmap(w_r);
    w_rule->show();

    w_back=new QLabel(this);
    w_back->setGeometry(450,530,185,60);
    QPixmap w_b;
    w_b.load(":/pic/rule_back.png");
    w_back->setScaledContents(1);
    w_back->setPixmap(w_b);
    w_back->show();
}
warm_tip::~warm_tip()
{

}

void warm_tip::mousePressEvent(QMouseEvent *e)
{
    if(e->x()>=450&&e->x()<=635&&e->y()>=530&&e->y()<=590)
    {
        this->close();
    }
}
