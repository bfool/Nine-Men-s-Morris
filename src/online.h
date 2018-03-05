#ifndef ONLINE_H
#define ONLINE_H

#include <QMainWindow>
#include <QtGui>
#include <QMessageBox>
#include <QLabel>
#include <QTextCodec>
#include  <QFileDialog>

#include <QWidget>
#include <QMap>
#include <QTcpSocket>
#include <QImage>

#include "logindilog.h"
#include "black_win.h"
#include "white_win.h"
#include "die_black_win.h"
#include "die_white_win.h"


class online : public QMainWindow
{
    Q_OBJECT

public:
    online(QWidget *parent = 0);
    ~online();

    void mousePressEvent(QMouseEvent *);

    QLabel *pic_board;
    QLabel *mylabel[17];

    black_win b_win;
    white_win w_win;

    void initial(void);
    void Black(void);
    void White(void);
    void click_pieces(char &colour);
    void move_pieces(char &colour);
    void fly_pieces(char &colour);
    void System(int &jude);

    int jude_move_up(void);
    int jude_move_down(void);
    int jude_three(void);
    void jude_result_near_pieces(char &colour);
    void jude_bug(int &step,int &jude);
    void jude_win_num_pieces(void);
    void jude_single(void);

    void eat_pieces(char &colour);
    int eat_or_not(void);
    void start(bool s);

    die_black_win d_b_win;
    die_white_win d_w_win;



signals:
    void draw();
    void clicked();
    void llocalDone(const QPoint &k);

private:
    struct Chess_Board              // !!**
        {
           char chess_board[8][8];
           int  black_num;          //棋子颜色为 ‘1’
           int  white_num;          //棋子颜色为 ‘0’
           int  temp_x;                //保存上次棋子的坐标
           int  temp_y;
           int  temp_second_x;         //保存起子的坐标，判断可以落子回起子点
           int  temp_second_y;
           int  temp_num;              //计总棋子个数
           int  three_num;              //计连成三子的个数
           int  fly_num;                //计飞子的步数
           char colour_piece;            //棋子颜色
        }board,temp_board;
    int x,y;
    bool show_or_hide;
    int move_step;
    int fly_step;
    bool switch_first_step;
    bool switch_second_step;
    bool switch_third_step;
    bool jude_repeat_pieces;
    bool jude_repeat_pieces2;
    bool jude_no_step;

    int map[19][19];
    int count;
    int p;
    int m,n;
    //NetGobang* b;
    QTcpSocket *socket;
    logindilog *ld;
    QMap<int, QPoint> localPoints;
    bool isLocal;
    bool isServer;

public slots:
    void draw_chess();
    void startGame(QTcpSocket *s, bool isServer);
    void draw_online();

private slots:
    void readData();
    void localDone(const QPoint &k);
};

#endif // MAINWINDOW_H
