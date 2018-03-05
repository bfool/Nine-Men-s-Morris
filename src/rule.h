#ifndef RULE_H
#define RULE_H

#include <QMainWindow>
#include <QtGui>
#include <QLabel>
#include <QPixmap>
#include <QDialog>
#include <phonon>
#include "game_window.h"

class game_rule : public QMainWindow
{
    Q_OBJECT

public:
    game_rule(QWidget *parent = 0);
    ~game_rule();

    QLabel *myrule;
    QLabel *r_back;

    void mousePressEvent(QMouseEvent *);

};

#endif // RULE_H
