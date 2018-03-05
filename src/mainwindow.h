#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include <QLabel>
#include <QPixmap>
#include <QDialog>
#include <phonon>
#include "game_window.h"
#include "rule.h"
#include "online.h"
#include "logindilog.h"
#include "warm_tip.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    game_window g;
    game_rule ru;

    online net_online;
    logindilog ld;

    warm_tip w_t;


    void initScence();
    void initBackground();
    void mousePressEvent(QMouseEvent *);
    QLabel *map;
    QLabel *start;
    QLabel *m1;
    QLabel *net1;
    QLabel *rule;

    QLabel *gamebt1_new;
    QLabel *gamebt2_new;

    Phonon::MediaObject *music;

    int choice;


public slots:
    void newgameWindow();

signals:
    void clicked();


};

#endif // MAINWINDOW_H
