#include "rule_in_game.h"

rule_in_game::rule_in_game(QWidget *parent)
    : QMainWindow(parent)
{
    this->setGeometry(300,60,1000,700);
    this->setMinimumSize(1000,700);
    this->setMaximumSize(1000,700);
    this->setWindowTitle("rule");
    //resize(1000,700);
    game_rule=new QLabel(this);
    QPixmap rg;
    rg.load(":/pic/gamerules.jpg");
    game_rule->setGeometry(0,0,1000,700);
    game_rule->setScaledContents(1);
    game_rule->setPixmap(rg);
    game_rule->show();

    g_back=new QLabel(this);
    g_back->setGeometry(600,540,180,55);
    QPixmap g_b;
    g_b.load(":/pic/rule_back.png");
    g_back->setScaledContents(1);
    g_back->setPixmap(g_b);
    g_back->show();
}
rule_in_game::~rule_in_game()
{

}

void rule_in_game::mousePressEvent(QMouseEvent *e)
{
    if(e->x()>=600&&e->x()<=780&&e->y()>=540&&e->y()<=595)
    {
        this->close();
    }
}
