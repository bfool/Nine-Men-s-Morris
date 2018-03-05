#ifndef DIE_BLACK_WIN_H
#define DIE_BLACK_WIN_H

#include <QtGui>
#include <QLabel>
#include <QPixmap>
class die_black_win : public QMainWindow
{
    Q_OBJECT

public:
    die_black_win(QWidget *parent = 0);
    ~die_black_win();

    QLabel *die_bk;
    QLabel *die_bk_ok;


    void mousePressEvent(QMouseEvent *);

};


#endif // DIE_BLACK_WIN_H
