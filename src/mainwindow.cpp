#include "mainwindow.h"
#include "game_window.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setGeometry(300,50,1000,700);
    this->setWindowTitle("menu");
    //resize(1000,700);
    this->setWindowFlags(this->windowFlags()&~Qt::WindowMaximizeButtonHint);
    this->setMinimumSize(1000,700);
    this->setMaximumSize(1000,700);

    Phonon::MediaObject *music=new Phonon::MediaObject(this);
    music->setCurrentSource(Phonon::MediaSource(":/pic/bk_music.mp3"));
    Phonon::AudioOutput *bk=new Phonon::AudioOutput(Phonon::MusicCategory,this);
    Phonon::Path path=Phonon::createPath(music,bk);
    music->play();

    initScence();
}

MainWindow::~MainWindow()
{

}

void MainWindow::initScence()
{
    map=new QLabel(this);
    map->setGeometry(0,0,1000,700);
    map->setScaledContents(1);
    QPixmap back;
    back.load(":/pic/main.jpg");    //background
    map->setScaledContents(1);
    map->setPixmap(back);


    m1=new QLabel(this);
    m1->setGeometry(200,20,580,120);
    QPixmap m_1;
    m_1.load(":/pic/main_1.png");
    m1->setScaledContents(1);//title
    m1->setPixmap(m_1);
    m1->show();


    start=new QLabel(this);
    start->setGeometry(80,230,330,120);
    QPixmap s1;
    s1.load(":/pic/main1.png");
    start->setScaledContents(1);
    start->setPixmap(s1);
    start->show();

    net1=new QLabel(this);
    net1->setGeometry(80,390,330,120);
    QPixmap s2;
    s2.load(":/pic/main2.png");
    net1->setScaledContents(1);
    net1->setPixmap(s2);
    net1->show();

    QLabel *m2=new QLabel(this);
    m2->setGeometry(80,550,330,120);
    QPixmap m_2;
    m_2.load(":/pic/quit.png");
    m2->setScaledContents(1);
    m2->setPixmap(m_2);
    m2->show();

    rule=new QLabel(this);
    rule->setGeometry(180,430,400,120);
    QPixmap s3;
    s3.load(":/pic/main3.png");
    rule->setScaledContents(1);
   // rule->setPixmap(s3);
   // rule->show();




    gamebt1_new=new QLabel(this);
    gamebt1_new->setGeometry(750,290,220,265);
    gamebt1_new->setScaledContents(1);
    QPixmap bt1_new;
    bt1_new.load(":/pic/new_main3.png");
    gamebt1_new->setPixmap(bt1_new);
    gamebt1_new->show();

    gamebt2_new=new QLabel(this);
    gamebt2_new->setGeometry(640,500,250,170);
    gamebt2_new->setScaledContents(1);
    QPixmap bt2_new;
    bt2_new.load(":/pic/new_main4.png");
    gamebt2_new->setPixmap(bt2_new);
    gamebt2_new->show();

}

void MainWindow::mousePressEvent(QMouseEvent *e)
{
   // if(e->x()>=0&&e->x()<=800&&e->y()>=200&&e->y()<=320)
  //  {
     if(e->x()>=80&&e->x()<=410&&e->y()>=230&&e->y()<=350)
       {
           //connect(this,SIGNAL(clicked()),this,SLOT(newgameWindow()));
           g.show();
        }
        else if(e->x()>=80&&e->x()<=410&&e->y()>=550&&e->y()<=770)
        {
            exit(1);
        }
     /*
        else if( QDialog::Rejected == ld.exec())
         {
             return;
         }
         else
         {
             QObject::connect(&ld, SIGNAL(connected(QTcpSocket*,bool)),&net_online, SLOT(startGame(QTcpSocket*,bool)));
             net_online.show();
         }
         */
   if(e->x()>=80&&e->x()<=410&&e->y()>=390&&e->y()<=510)
        {
             net_online.show();
             ld.show();

             QObject::connect(&ld, SIGNAL(connected(QTcpSocket*,bool)),&net_online, SLOT(startGame(QTcpSocket*,bool)));
        }
         else if(e->x()>=750&&e->x()<=970&&e->y()>=290&&e->y()<=555)
        {
            ru.show();
        }
        else if(e->x()>=640&&e->x()<=890&&e->y()>=500&&e->y()<=670)
        {
            w_t.show();
        }

//}

    emit clicked();
}

void MainWindow::newgameWindow()
{
    g.show();
}
