#ifndef BLACK_WIN_H
#define BLACK_WIN_H

#include <QtGui>
#include <QLabel>
#include <QPixmap>
class black_win : public QMainWindow
{
    Q_OBJECT

public:
    black_win(QWidget *parent = 0);
    ~black_win();

    QLabel *black_bk;
    QLabel *black_win_back;
    QLabel *black_ok;


    void mousePressEvent(QMouseEvent *);

};


#endif // BLACK_WIN_H
