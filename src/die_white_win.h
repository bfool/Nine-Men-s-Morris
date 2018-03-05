#ifndef DIE_WHITE_WIN_H
#define DIE_WHITE_WIN_H

#include <QtGui>
#include <QLabel>
#include <QPixmap>
class die_white_win : public QMainWindow
{
    Q_OBJECT

public:
    die_white_win(QWidget *parent = 0);
    ~die_white_win();

    QLabel *die_wk;
    QLabel *die_wk_ok;

    void mousePressEvent(QMouseEvent *);

};

#endif // DIE_WHITE_WIN_H
