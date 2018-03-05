#ifndef WHITE_WIN_H
#define WHITE_WIN_H

#include <QtGui>
#include <QLabel>
#include <QPixmap>
class white_win : public QMainWindow
{
    Q_OBJECT

public:
    white_win(QWidget *parent = 0);
    ~white_win();

    QLabel *white_bk;
    QLabel *white_win_back;
    QLabel *white_ok;


    void mousePressEvent(QMouseEvent *);

};

#endif // WHITE_WIN_H
