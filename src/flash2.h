#ifndef FLASH2_H
#define FLASH2_H

#include <QMainWindow>
#include <QtGui>
#include <QLabel>
#include <QPixmap>

#include "mainwindow.h"

class flash2 : public QMainWindow
{
    Q_OBJECT

public:
    flash2(QWidget *parent = 0);
    ~flash2();

    QLabel *main_map;
    QLabel *main_start;
    void mousePressEvent(QMouseEvent *);

    MainWindow w;

public slots:
    void enter_game();

signals:
    void clicked();

};

#endif // FLASH2_H
