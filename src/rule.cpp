#include "rule.h"

game_rule::game_rule(QWidget *parent)
    : QMainWindow(parent)
{
    this->setGeometry(300,40,1024,791);
    this->setMinimumSize(1024,791);
    this->setMaximumSize(1024,791);
    this->setWindowTitle("rule");
    //resize(1024,791);
    QLabel *myrule=new QLabel(this);
    QPixmap r;
    r.load(":/pic/rules.jpg");
    myrule->setGeometry(0,0,1024,791);
    myrule->setPixmap(r);
    myrule->show();

    QLabel *r_back=new QLabel(this);
    r_back->setGeometry(600,615,250,80);
    QPixmap r_b;
    r_b.load(":/pic/rule_back.png");
    r_back->setScaledContents(1);
    r_back->setPixmap(r_b);
    r_back->show();
}
game_rule::~game_rule()
{

}

void game_rule::mousePressEvent(QMouseEvent *e)
{
    if(e->x()>=600&&e->x()<=850&&e->y()>=615&&e->y()<=695)
    {
        this->close();
    }
}
