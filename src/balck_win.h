#ifndef BALCK_WIN_H
#define BALCK_WIN_H

#include <QtGui>
#include <QLabel>
#include <QPixmap>
class black_win : public QMainWindow
{
    Q_OBJECT

public:
    black_win(QWidget *parent = 0);
    ~black_win();

    void mousePressEvent(QMouseEvent *);

};

#endif // BALCK_WIN_H
