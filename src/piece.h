#ifndef PIECE_H
#define PIECE_H

#include <QtGui>
#include <QLabel>
#include <QPixmap>
class piece : public QMainWindow
{
    Q_OBJECT

public:
    piece(QWidget *parent = 0);
    ~piece();

    QLabel *piece_bk;
    QLabel *piece_or_not;

    void mousePressEvent(QMouseEvent *);

};


#endif // PIECE_H
