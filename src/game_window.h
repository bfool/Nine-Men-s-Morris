#ifndef GAME_WINDOW_H
#define GAME_WINDOW_H
#include <QMainWindow>
#include <QtGui>
#include <QMessageBox>
#include <QLabel>
#include <QTextCodec>
#include  <QFileDialog>
#include <phonon>

#include "rule_in_game.h"
#include "black_win.h"
#include "white_win.h"
#include "piece.h"
#include "die_black_win.h"
#include "die_white_win.h"

class game_window : public QMainWindow
{
    Q_OBJECT

public:
    game_window(QWidget *parent = 0);
    ~game_window();
    QLabel *pic_board;
    void mousePressEvent(QMouseEvent *);


    QLabel *mylabel[17];

    QLabel *gamebt1;
    QLabel *gamebt2;
    QLabel *gamebt3;



    QLabel *tip1;
    QLabel *tip2;
    QLabel *tip3;
    QLabel *tip4;
    QLabel *tip5;
    QLabel *tip6;


    rule_in_game rulegame;
    black_win b_win;
    white_win w_win;
    piece p_or_not;
    die_black_win d_b_win;
    die_white_win d_w_win;


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

    int juge_factory;



signals:
    void clicked();
    void sgn1();

private:
    struct Chess_Board
    {
       char chess_board[8][8];
       int  black_num;          //棋子颜色为 ‘1’
       int  white_num;          //棋子颜色为 ‘0’
       int  temp_x;                //保存上次棋子的坐� �
       int  temp_y;
       int  temp_second_x;         //保存起子的坐� �，判断可以落子回起子点
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
public slots:
    void draw_chess();
};

#endif // GAME_WINDOW_H
