#ifndef WARM_TIP_H
#define WARM_TIP_H

#include <QMainWindow>
#include <QtGui>
#include <QLabel>
#include <QPixmap>
#include "game_window.h"

class warm_tip : public QMainWindow
{
    Q_OBJECT

public:
    warm_tip(QWidget *parent = 0);
    ~warm_tip();

    QLabel *w_rule;
    QLabel *w_back;

    void mousePressEvent(QMouseEvent *);

};
#endif // WARM_TIP_H
