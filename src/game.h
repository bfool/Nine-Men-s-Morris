#ifndef GAME_H
#define GAME_H
#include <QMainWindow>
#include <QtGui>
#include <QMessageBox>
#include <QLabel>

class mygame : public QMainWindow
{
    Q_OBJECT

public:
    mygame(QWidget *parent = 0);
    ~mygame();

   // void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);
    QLabel *board;
    QLabel *mylabel[17];

signals:
    void clicked();

private:
    int map[19][19];
    int count;
    int p;
    int x,y;
    //int judge_three(int,int);
public slots:
    void draw_chess();

};

#endif // GAME_H
