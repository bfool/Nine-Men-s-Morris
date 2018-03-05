#ifndef RULE_IN_GAME_H
#define RULE_IN_GAME_H
#include <QtGui>
#include <QLabel>
#include <QPixmap>
class rule_in_game : public QMainWindow
{
    Q_OBJECT

public:
    rule_in_game(QWidget *parent = 0);
    ~rule_in_game();

    QLabel *game_rule;
    QLabel *g_back;

    void mousePressEvent(QMouseEvent *);

};
#endif // RULE_IN_GAME_H
