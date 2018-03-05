#include "mainwindow.h"
#include "game_window.h"
#include "rule_in_game.h"
#include "black_win.h"
#include "white_win.h"
#include "die_black_win.h"
#include "die_white_win.h"

game_window::game_window(QWidget *parent)
    : QMainWindow(parent)
{
    QTextCodec::setCodecForLocale(QTextCodec::codecForLocale());
    juge_factory=0;
    initial();
    //resize(1200,800);
    this->setGeometry(200,10,1200,800);
    this->setWindowFlags(this->windowFlags()&~Qt::WindowMaximizeButtonHint);
    this->setWindowTitle("singer game");
    this->setMinimumSize(1200,800);
    this->setMaximumSize(1200,800);
    count=1;
    int i;
    p=1;
    show_or_hide=0;
    move_step=0;
    fly_step=0;
    switch_second_step=0;
    switch_third_step=0;
    jude_repeat_pieces=0;
    jude_repeat_pieces2=0;
    jude_no_step=0;

    pic_board=new QLabel(this);
    pic_board->setGeometry(0,0,1200,800);
    QPixmap pix;
    pix.load(":/pic/board.jpg");
    pic_board->setScaledContents(1);
    pic_board->setPixmap(pix);

    for(i=1;i<=16;i++)
    {
        mylabel[i]=new QLabel(this);
    }

    mylabel[1]->setGeometry(35,35,60,60);
    mylabel[2]->setGeometry(380,35,60,60);
    mylabel[3]->setGeometry(730,35,60,60);

    mylabel[4]->setGeometry(205,200,60,60);
    mylabel[5]->setGeometry(382,200,60,60);
    mylabel[6]->setGeometry(558,200,60,60);

    mylabel[7]->setGeometry(35,364,60,60);
    mylabel[8]->setGeometry(207,364,60,60);
    mylabel[9]->setGeometry(558,364,60,60);
    mylabel[10]->setGeometry(730,364,60,60);

    mylabel[11]->setGeometry(205,550,60,60);
    mylabel[12]->setGeometry(385,550,60,60);
    mylabel[13]->setGeometry(558,550,60,60);

    mylabel[14]->setGeometry(35,700,60,60);
    mylabel[15]->setGeometry(390,700,60,60);
    mylabel[16]->setGeometry(730,700,60,60);


    gamebt1=new QLabel(this);
    gamebt1->setGeometry(810,270,350,110);
    QPixmap bt1;
    bt1.load(":/pic/gamebutton1.png");
    gamebt1->setScaledContents(1);
    gamebt1->setPixmap(bt1);
    gamebt1->show();

    gamebt2=new QLabel(this);
    gamebt2->setGeometry(810,445,350,110);
    QPixmap bt2;
    bt2.load(":/pic/gamebutton2.png");
    gamebt2->setScaledContents(1);
    gamebt2->setPixmap(bt2);
    gamebt2->show();

    gamebt3=new QLabel(this);
    gamebt3->setGeometry(810,625,350,110);
    QPixmap bt3;
    bt3.load(":/pic/gamebutton3.png");
    gamebt3->setScaledContents(1);
    gamebt3->setPixmap(bt3);
    gamebt3->show();





    tip1=new QLabel(this);
    tip1->setGeometry(890,90,200,100);
    tip1->setScaledContents(1);
    QPixmap t1;
    t1.load(":/pic/tip1.png");//first tip
    tip1->setPixmap(t1);
    tip1->show();


    tip2=new QLabel(this);
    tip2->setGeometry(890,140,200,50);
    tip2->setScaledContents(1);
    QPixmap t2;
    t2.load(":/pic/stage2.png");    //factory
    tip2->setPixmap(t2);
    tip2->hide();

    tip3=new QLabel(this);
    tip3->setGeometry(890,90,200,50);
    tip3->setScaledContents(1);
    QPixmap t3;
    t3.load(":/pic/stage1.png");       //put stage
    tip3->setPixmap(t3);
    tip3->hide();

    tip4=new QLabel(this);
    tip4->setGeometry(890,90,200,50);
    tip4->setScaledContents(1);
    QPixmap t4;
    t4.load(":/pic/stage3.png");    //move stage
    tip4->setPixmap(t4);
    tip4->hide();

    tip5=new QLabel(this);
    tip5->setGeometry(890,90,200,50);
    QPixmap t5;
    t5.load(":/pic/stage4.png");    //fly stage
    tip5->setScaledContents(1);
    tip5->setPixmap(t5);
    tip5->hide();


/*
    QLabel *stage2=new QLabel(this);
    stage2->setGeometry(890,90,200,100);
    stage2->setScaledContents(1);
    QPixmap s2;
    s2.load(":/stage2.png");
    stage2->setPixmap(s2);
    */

    connect(this,SIGNAL(clicked()),this,SLOT(draw_chess()));

}

game_window::~game_window()
{

}

void game_window::initial(void)

{
    int i,j;
    board.three_num=0;
    board.fly_num=0;
    board.temp_num=0;
    board.black_num=0;
    board.white_num=0;
    board.temp_second_x=0;
     board.temp_second_y=0;
     board.colour_piece=' ';
    for(i=0;i<5;i++)
    {
        for(j=0;j<5;j++)
        {
            board.chess_board[i][j]=' ';
            temp_board.chess_board[i][j]='0';
        }
    }
    board.chess_board[0][0]='#';
    board.chess_board[0][2]='#';
    board.chess_board[0][4]='#';
    board.chess_board[1][1]='#';
    board.chess_board[1][2]='#';
    board.chess_board[1][3]='#';
    board.chess_board[2][0]='#';
    board.chess_board[2][1]='#';
    board.chess_board[2][3]='#';
    board.chess_board[2][4]='#';
    board.chess_board[3][1]='#';
    board.chess_board[3][2]='#';
    board.chess_board[3][3]='#';
    board.chess_board[4][0]='#';
    board.chess_board[4][2]='#';
    board.chess_board[4][4]='#';
}

void game_window::System(int &jude)
{
    if(jude==1)
    {
        if(jude_three()==1)
        {
            tip2->hide();
            if(!switch_second_step)
            tip3->show();
            /*
            tip1->hide();
            tip2->show();   //factory
            */
            //tip3 show
        }
        else if(switch_second_step==1)
        {
            /*
            tip3->hide();//put
            tip4->show();//move
            */
            tip3->hide();
            if(jude_three()==1)
            {
                tip2->show();
                tip3->hide();
            }
        }
        /*
        else if(switch_third_step==1)
        {
            tip4->hide();
            if(jude_three()==1)
            {
                tip2->show();
            }
           // tip5->show();//fly
        }
        */
        //tip2->hide();
        //tip3->show();

        //QMessageBox::information(this, "Win", "Win", QMessageBox::Ok);
        eat_pieces(board.colour_piece);

    }
    else if(jude==0)
    {

        if(move_step==0 && fly_step==0)          //到第二阶段（移完第一个子后），会执行count++,进入正常的移子阶段
        {
            count++;
            if(switch_second_step==1 && switch_third_step==0)       //进入正常的移子阶段后，开关是打开着的，每次都会进入移子的第一次判断
            {
                move_step=1;
            }
            if(switch_third_step==1)
            {
                fly_step=1;
            }
        }
        else if(switch_second_step==0 && switch_third_step==1 && fly_step==0)
        {
            count++;
            if(switch_third_step==1)
            {
                fly_step=1;
            }
        }
        if(count%2+1==1)
        {
            Black();
        }
        else if(count%2+1==2)
        {
            White();
        }

    }
}

void game_window::White(void)
{
    if(board.white_num<6 && board.temp_num<12)
    {
        board.colour_piece='2';
        click_pieces(board.colour_piece);
    }
    else if(board.white_num>3 && board.temp_num==12)
    {
        board.colour_piece='2';
        move_pieces(board.colour_piece);
    }
    else if(board.white_num==3 && board.temp_num==12)
    {
        board.colour_piece='2';
        fly_pieces(board.colour_piece);
    }
}

void game_window::Black(void)
{
    if(board.black_num<6 && board.temp_num<12)
    {
        board.colour_piece='1';
        click_pieces(board.colour_piece);
    }
    else if(board.black_num>3 && board.temp_num==12)
    {
        board.colour_piece='1';
        move_pieces(board.colour_piece);
    }
    else if(board.black_num==3 && board.temp_num==12)
    {
        board.colour_piece='1';
        fly_pieces(board.colour_piece);
    }
}

void game_window::click_pieces(char &colour)
{
    switch_first_step=1;
    if(colour=='1')
    {
        board.chess_board[x][y]=colour;
        map[m][n]=1;
        board.black_num++;
    }
    else if(colour=='2')
    {
        board.chess_board[x][y]=colour;
        map[m][n]=2;
        board.white_num++;
    }

    board.temp_num++;
    board.temp_x=x;
    board.temp_y=y;

    if(board.temp_num==12)              //判断进入第二阶段
    {
        move_step=0;
        switch_second_step=1;
    }
}

void game_window::move_pieces(char &colour)
{
    switch_first_step=0;
    if(move_step==1)
    {
        if(jude_move_up()==0)
        {
            if(board.colour_piece=='1')
                            board.colour_piece='2';
                        else
                            board.colour_piece='1';
            return;
        }
        move_step=2;
        show_or_hide=1;

        if(colour=='1')
        {
            map[m][n]=1;
        }
        else if(colour=='2')
        {
            map[m][n]=2;
        }
        board.chess_board[x][y]='#';

        board.temp_second_x=x;
        board.temp_second_y=y;

        return;
    }
    else if(move_step==2)
    {
        if(jude_move_down()==0)
        {
            return;
        }
        move_step=0;
        show_or_hide=0;
        if(colour=='1')
        {
            map[m][n]=1;
        }
        else if(colour=='2')
        {
            map[m][n]=2;
        }
        board.chess_board[x][y]=colour;
    }
    board.temp_x=x;
    board.temp_y=y;

    if(board.temp_second_x==x && board.temp_second_y==y)
       {
           if(board.colour_piece=='2')
               board.colour_piece='1';
           else
               board.colour_piece='2';
           return;
       }

    if((board.white_num==3 || board.black_num==3) && board.temp_num==12)       //判断是否有进入第三阶段的,如果存在，下一回合为飞子阶段
    {
       switch_third_step=1;
       fly_step=0;
    }
}

void game_window::fly_pieces(char &colour)
{
        if(fly_step==1)
        {
            fly_step=2;
            show_or_hide=1;

            if(colour=='1')
            {
                map[m][n]=1;
            }
            else if(colour=='2')
            {
                map[m][n]=2;
            }
            board.chess_board[x][y]='#';

            board.temp_second_x=x;
            board.temp_second_y=y;


            return;
        }
        else if(fly_step==2)
        {
            fly_step=0;
            show_or_hide=0;

            if(colour=='1')
            {               
                map[m][n]=1;
            }
            else if(colour=='2')
            {
                map[m][n]=2;
            }
            board.chess_board[x][y]=colour;
        }

        board.temp_x=x;
        board.temp_y=y;

        if(board.black_num==3 && board.white_num==3)
            board.fly_num++;

        if(board.temp_second_x==x && board.temp_second_y==y )
                {
                    if(board.colour_piece=='2')
                        board.colour_piece='1';
                    else
                        board.colour_piece='2';
                    count--;
                    return;
                }


        if(switch_second_step==1)           //如果还有一方是第二阶段的，那下一回合就关闭第三阶段的判断
        {
            switch_third_step=0;
        }
        /*if(board.fly_num==6)                      //设计窗口,此时跳出对话框，询问是否和棋
         {
             printf("和棋！是否同意? (0)同意  (1)不同意");
             scanf("%d",&i);
         }*/
}
void game_window::eat_pieces(char &colour)
{
    while(eat_or_not()==1)
     {
         return;
     }

     if(colour=='1')             //colour为当前执行的棋子，所以 另一方棋子减 1
     {
         map[m][n]=2;
         board.white_num--;
     }
     else if(colour=='2')
     {
         map[m][n]=1;
         board.black_num--;
     }

     show_or_hide=1;
     board.chess_board[x][y]='#';

     board.temp_x=x;
     board.temp_y=y;

     if((board.white_num==3 && board.black_num==3) && board.temp_num==12)
     {
         switch_second_step=0;
         switch_third_step=1;

         fly_step=0;
         move_step=3;       //关闭第二阶段
         return;
     }

     else if(board.temp_num==12 && (board.black_num==2 || board.white_num==2))
     {
        jude_win_num_pieces();
     }
     if(jude_repeat_pieces==1)        //判断已经存在的三子
     {
         switch_third_step=0;
         jude_repeat_pieces=0;
         jude_repeat_pieces2=1;
         return;
     }
     if((board.white_num==3 || board.black_num==3) && board.temp_num==12)       //判断是否有进入第三阶段的
     {
         if(jude_repeat_pieces2==0)            //两个开关（jude_repeat_pieces），防止只有三子方第三次吃子后又进入飞子阶段
         {
             switch_third_step=1;
             fly_step=0;
             jude_repeat_pieces=1;
         }
         else if(jude_repeat_pieces2==1)
         {
             jude_repeat_pieces2=0;
         }
     }
}

int game_window::eat_or_not()
{
    int i,j,jude=0,jude1=0,jude2=0;

      if(board.three_num==2 || board.three_num==3)                                    //判断双方个三子，都为磨坊的情况
       {
            for(i=0;i<5;i++)
            {
                for(j=0;j<5;j++)
                {
                    if(board.chess_board[i][j]=='2' || board.chess_board[i][j]=='1')
                        jude++;
                }
            }
            if(jude==6||jude==8||jude==10)
                jude2=1;
        }

        i=x;
        j=y;
        if(board.chess_board[i][j]=='#' || board.chess_board[i][j]==' ')
        {
           jude1=1;
        }
        if(i==0 || i==4 || (i==0 && j==2) || (i==4 && j==2))
        {
            j=0;
            if(board.chess_board[i][j]==board.chess_board[i][j+2] && board.chess_board[i][j]==board.chess_board[i][j+4] && board.chess_board[i][j+2]==board.chess_board[i][j+4])
            {
                 jude1=1;
            }
        }
        else if(i==1 || i==3 || (i==1 && j==2) || (i==3 && j==2))
        {
            j=1;
            if(board.chess_board[i][j]==board.chess_board[i][j+1] && board.chess_board[i][j]==board.chess_board[i][j+2] && board.chess_board[i][j+1]==board.chess_board[i][j+2])
            {
                 jude1=1;
            }
        }

        i=x;
        j=y;
        if(j==0 || j==4 || (j==0 && i==2) || (j==4 && i==2))
        {
            i=0;
            if(board.chess_board[i][j]==board.chess_board[i+2][j] && board.chess_board[i][j]==board.chess_board[i+4][j] && board.chess_board[i+2][j]==board.chess_board[i+4][j])
            {
               jude1=1;
            }
        }
        else if(j==1 || j==3 || (j==1 && i==2) || (j==3 && i==2))
        {
            i=1;
            if(board.chess_board[i][j]==board.chess_board[i+1][j] && board.chess_board[i][j]==board.chess_board[i+2][j] && board.chess_board[i+1][j]==board.chess_board[i+2][j])
            {
                 jude1=1;
            }
        }
        if(jude1==1 && jude2==1)
        {
            return 0;
        }
        else if(jude1==1)
            return 1;
        return 0;
}

int game_window::jude_three(void)
{
    int i,j,jude=0;
    board.three_num=0;

    if(jude_no_step==1)
    {
        jude_no_step=0;
        return 0;
    }
    if(board.temp_second_x==board.temp_x && board.temp_second_y==board.temp_y)
    {
        jude_no_step=1;
        return 0;
    }

    for(i=0;i<5;i++)
    {
        j=0;
        if((board.chess_board[i][j]!='#') && (board.chess_board[i][j]==board.chess_board[i][j+2]) && (board.chess_board[i][j]==board.chess_board[i][j+4]) && (board.chess_board[i][j+2]==board.chess_board[i][j+4]))
        {
            board.three_num++;
            if(i==board.temp_x)
            {
                jude=1;
            }
        }
        j=1;
        if((board.chess_board[i][j]!='#') && (board.chess_board[i][j]==board.chess_board[i][j+1]) && (board.chess_board[i][j]==board.chess_board[i][j+2]) && (board.chess_board[i][j+1]==board.chess_board[i][j+2]))
        {
            board.three_num++;
            if(i==board.temp_x)
            {
                jude=1;
            }
        }
    }
    for(j=0;j<5;j++)
    {
        i=0;
        if((board.chess_board[i][j]!='#') && (board.chess_board[i][j]==board.chess_board[i+2][j]) && (board.chess_board[i][j]==board.chess_board[i+4][j]) && (board.chess_board[i+2][j]==board.chess_board[i+4][j]))
        {
            board.three_num++;
            if(j==board.temp_y)
            {
                jude=1;
            }
        }
        i=1;
        if((board.chess_board[i][j]!='#') && (board.chess_board[i][j]==board.chess_board[i+1][j]) && (board.chess_board[i][j]==board.chess_board[i+2][j]) && (board.chess_board[i+1][j]==board.chess_board[i+2][j]))
        {
            board.three_num++;
            if(j==board.temp_y)
            {
                jude=1;
            }
        }
    }
    if(jude==1)
    {
        return 1;
    }
    else {return 0;}
}

int game_window::jude_move_up()
{
    int jude=0;
    if(x==0 || x==4 ||(x==0 && y==2) || (x==4 && y==2) || (x==2 && y==0) || (x==2 && y==4))
    {
        if(board.chess_board[x][y+2]=='#' || board.chess_board[x][y-2]=='#' || board.chess_board[x+2][y]=='#' || board.chess_board[x-2][y]=='#')
        {
            jude=1;
            if(board.chess_board[x][y+2]=='#')
            {
                temp_board.chess_board[x][y+2]='1';
            }
            if(board.chess_board[x][y-2]=='#')
            {
                temp_board.chess_board[x][y-2]='1';
            }
            if(board.chess_board[x+2][y]=='#')
            {
                temp_board.chess_board[x+2][y]='1';
            }
            if(board.chess_board[x-2][y]=='#')
            {
                temp_board.chess_board[x-2][y]='1';
            }
        }
    }
    else if(x==1 || x==3 || (x==1 && y==2) || (x==3 && y==2) || (x==2 && y==1) || (x==2 && y==3))
    {
        if(board.chess_board[x][y+1]=='#' || board.chess_board[x][y-1]=='#' || board.chess_board[x+1][y]=='#' || board.chess_board[x-1][y]=='#')
        {
             jude=1;
             if(board.chess_board[x][y+1]=='#')
             {
                 temp_board.chess_board[x][y+1]='1';
             }
             if(board.chess_board[x][y-1]=='#')
             {
                 temp_board.chess_board[x][y-1]='1';
             }
             if(board.chess_board[x+1][y]=='#')
             {
                 temp_board.chess_board[x+1][y]='1';
             }
             if(board.chess_board[x-1][y]=='#')
             {
                 temp_board.chess_board[x-1][y]='1';
             }
        }
    }
    if((x==0 && y==2) || (x==1 && y==2) || (x==3 && y==2) || (x==4 && y==2) )
    {
        if(board.chess_board[x-1][y]=='#' || board.chess_board[x+1][y]=='#')
        {
             jude=1;
             if(board.chess_board[x-1][y]=='#')
             {
                 temp_board.chess_board[x-1][y]='1';
             }
             if(board.chess_board[x+1][y]=='#')
             {
                 temp_board.chess_board[x+1][y]='1';
             }
        }
    }
    else if((x==2 && y==0) || (x==2 && y==1) || (x==2 && y==3) || (x==2 && y==4))
    {
        if(board.chess_board[x][y+1]=='#' || board.chess_board[x][y-1]=='#')
        {
             jude=1;
             if(board.chess_board[x][y+1]=='#')
             {
                 temp_board.chess_board[x][y+1]='1';
             }
             if(board.chess_board[x][y-1]=='#')
             {
                 temp_board.chess_board[x][y-1]='1';
             }
        }
    }
    if(jude==1)
    {
        return 1;
    }
    else  {return 0;}
}

int game_window::jude_move_down()
{
    int i,j,jude=0;
    for(i=0;i<5;i++)
    {
        for(j=0;j<5;j++)
        {
            if(temp_board.chess_board[i][j]=='1' && (x==i && y==j))
            {
                jude=1;
            }
        }
    }
    if(board.temp_second_x==x && board.temp_second_y==y)
    {
        jude=1;
        count--;
    }
    if(jude==1)
    {
        for(i=0;i<5;i++)
        {
            for(j=0;j<5;j++)
            {
                temp_board.chess_board[i][j]='0';
            }
        }
        return 1;
    }
    else    {return 0;}
}

void game_window::jude_result_near_pieces(char &colour_piece)
{
    int i=0,j=0;
    char colour;
        if(board.temp_second_x==x && board.temp_second_y==y)
        {
            if(colour_piece=='1')
                colour='2';
            else if(colour_piece=='0')
                colour='1';
        }
        else
        {
            colour=colour_piece;
        }
    for(i=0;i<5;i++)
    {
        for(j=0;j<5;j++)
        {
            if(board.chess_board[i][j]=='#' || board.chess_board[i][j]==' ' )          //判断棋盘数组，不为可落子点 或 无子，则跳过
            {
                 continue;
            }
            else
            {
                if((i==0 && j==2) || (i==4 && j==2))
                {
                    if((board.chess_board[i][j+2]=='#') || (board.chess_board[i][j-2]=='#') || (board.chess_board[i+1][j]=='#') || (board.chess_board[i-1][j]=='#'))
                    {
                        if(board.chess_board[i][j]!=colour)
                        {
                            return;
                        }

                    }
                }
                else if((i==2 && j==0) || (i==2 && j==4))
                {
                    if((board.chess_board[i+2][j]=='#') || (board.chess_board[i-2][j]=='#') || (board.chess_board[i][j+1]=='#') || (board.chess_board[i][j-1]=='#'))
                    {
                        if(board.chess_board[i][j]!=colour)
                        {
                            return;
                        }

                    }
                }
                else if((i==1 && j==2) || (i==3 && j==2) || (i==2 && j==1) || (i==2 && j==3))
                {
                    if((board.chess_board[i][j+1]=='#') || (board.chess_board[i][j-1]=='#') || (board.chess_board[i+1][j]=='#') || (board.chess_board[i-1][j]=='#'))
                    {
                        if(board.chess_board[i][j]!=colour)
                        {
                            return;
                        }
                    }
                }

                if(i==0||i==4||j==0||j==4)
                {
                    if((board.chess_board[i][j+2]=='#') || (board.chess_board[i][j-2]=='#') || (board.chess_board[i+2][j]=='#') || (board.chess_board[i-2][j]=='#'))
                    {
                        if(board.chess_board[i][j]!=colour)
                        {
                            return;
                        }
                    }
                }
                else if(i==1||i==3||j==1||j==3)
                {
                    if((board.chess_board[i+1][j]=='#') || (board.chess_board[i-1][j]=='#') || (board.chess_board[i][j+1]=='#') || (board.chess_board[i][j-1]=='#'))
                    {
                        if(board.chess_board[i][j]!=colour)
                        {
                            return;
                        }

                    }
                }
            }
        }
    }
    QTextStream cout(stdout,QIODevice::WriteOnly);
                   QString str,str2;
                   str2=board.colour_piece;
                   str="围死";
                   cout.flush();
                   cout<<str<<endl
                         <<str2<<endl;

    if(colour=='2')                   //设计窗口
    {
       // printf("白方胜利！");
       // exit(0);
        d_w_win.show();
         tip1->hide();
         tip2->hide();
         tip3->hide();
         tip4->hide();
         tip5->hide();
    }
    else if(colour=='1')
    {
       // printf("黑方胜利！");
       // exit(0);
        d_b_win.show();
        tip1->hide();
        tip2->hide();
        tip3->hide();
        tip4->hide();
        tip5->hide();
    }
}
void game_window::jude_bug(int &step,int &jude)
{
    if((step==0 || step==1) && (board.chess_board[x][y]==board.colour_piece || board.chess_board[x][y]=='#'))
    {
        if(step==1 && board.chess_board[x][y]==board.colour_piece && board.temp_second_x==x && board.temp_second_y)        //如果第二阶段起子返回 ，则颜色还为上一色，仍继续进入
        {
            System(jude);
        }
        if(board.chess_board[x][y]==board.colour_piece)
        {
            return;
        }

    }
    else if(board.chess_board[x][y]=='#' && x==board.temp_second_x && y==board.temp_second_y)         //当子没进行移动 落回原点的话 ，落子阶段能正常进行
    {
        System(jude);
    }
    else if(step==2 && (board.chess_board[x][y]!='#'))
    {
        return;
    }
    else
    {
        System(jude);
    }
}
void game_window::jude_single(void)
{
    int jude=0;

    if(board.temp_num>=5)                       //当总落子数为5颗以上才会 判断工厂
        jude=jude_three();
    if(jude==0)
    {
        juge_factory=0;
        if(board.temp_num==12)
        {
            if(switch_second_step==1)
            {
                if((board.black_num==3 || board.white_num==3) && switch_third_step==1)
                {
                    jude_bug(fly_step,jude);
                }
                else
                {
                    jude_bug(move_step,jude);
                }
            }
           else if(switch_third_step==1 && board.black_num==3 && board.white_num==3)
           {
                jude_bug(fly_step,jude);
           }
        }
        else
        {
            if(board.chess_board[x][y]=='2'|| board.chess_board[x][y]=='1')
            {
                return;
            }
            else
            {
                 System(jude);
            }
        }
    }
    else if(jude==1)
    {
        juge_factory=1;
        if(board.chess_board[x][y]==board.colour_piece || board.chess_board[x][y]=='#')
        {
            return;
        }
        else
        {
              System(jude);
        }

    }
}

void game_window::jude_win_num_pieces(void)
{
    QTextCodec::setCodecForLocale(QTextCodec::codecForLocale());

    QTextStream cout(stdout,QIODevice::WriteOnly);
    QString str;

    if(board.black_num<=2)                      //设计弹出窗口，询问退出 或 开始下一盘
    {
        str="白方胜利!";
        cout<<str<<endl;
        w_win.show();
    }
    else if(board.white_num<=2)
    {
        str="黑方胜利!";
        cout<<str<<endl;
        b_win.show();
    }
}

void game_window::draw_chess()
{
    int i,j;
    for(i=0;i<19;i++)
    {
        for(j=0;j<19;j++)
        {
            if(map[i][j]==1)
            {
                QPixmap chess1;
                chess1.load(":/pic/black.png");
                mylabel[p]->setScaledContents(1);
                mylabel[p]->setPixmap(chess1);

                if(show_or_hide==0)
                { /*
                      tip1  first
                      tip2  factory
                      tip3  put
                      tip4  move
                      */

                    if(jude_three()==1)
                    {
                        tip1->hide();
                        tip2->show();
                    }

                    if(switch_second_step==1)
                    {
                        tip1->hide();
                        tip2->hide();
                        tip3->hide();
                        tip4->show();
                        if(jude_three()==1)
                        {
                            tip2->show();
                            tip3->hide();
                        }
                    }
                    if(board.fly_num==6)
                    {
                        p_or_not.show();
                    }
                    /*
                    if(switch_third_step==1&&switch_second_step==1)
                    {
                        tip1->hide();
                        tip2->hide();
                        tip3->hide();
                        tip4->hide();
                        tip5->show();
                        if(jude_three()==1)
                        {
                            tip2->show();
                        }
                    }
                    */

                    mylabel[p]->show();
                    //sd->play();

                }
                else if(show_or_hide==1)
                {
                    board.chess_board[x][y]='#';

                     mylabel[p]->hide();
                     show_or_hide=0;
                }
            }
            else if(map[i][j]==2)
            {
                QPixmap chess2;
                chess2.load(":/pic/white.png");
                mylabel[p]->setScaledContents(1);
                mylabel[p]->setPixmap(chess2);

                if(show_or_hide==0)
                {

                    if(jude_three()==1)
                    {
                        tip1->hide();
                        tip2->show();
                        //tip3 show
                    }

                    if(switch_second_step==1)
                    {
                        tip1->hide();
                        tip2->hide();
                        tip3->hide();
                        tip4->show();
                        if(jude_three()==1)
                        {
                            tip2->show();
                            tip3->hide();
                        }
                    }
                    /*
                    if(switch_third_step==1&&switch_second_step==1)
                    {
                        tip1->hide();
                        tip2->hide();
                        tip3->hide();
                        tip4->hide();
                        tip5->show();
                        if(jude_three()==1)
                        {
                            tip2->show();
                        }
                    }
                    */
                    if(board.fly_num==6)
                    {
                        p_or_not.show();
                    }
                    mylabel[p]->show();

                }
                else if(show_or_hide==1)
                {
                    board.chess_board[x][y]='#';
                    mylabel[p]->hide();
                    show_or_hide=0;
                }
            }
        }
    }
    if(move_step!=2 && switch_third_step==0 && board.black_num!=3 && board.white_num!=3 && board.temp_num==12)
        {
            jude_result_near_pieces(board.colour_piece);
        }
}

void game_window::mousePressEvent(QMouseEvent *e)
{
    memset(map,0,19*19*sizeof(int));

    if(e->x()>=0&&e->x()<=1200&&e->y()>=0&&e->y()<=800)
    {
       if(e->x()>=25 && e->x()<=105 && e->y()>=25 && e->y()<=105)
       {
           m=1;n=1;
           p=1;
           x=0;y=0;
       }
       else if(e->x()>=370 && e->x()<=450 && e->y()>=25&&e->y()<=105)
       {
           m=9;n=1;
           p=2;
           x=0;y=2;
       }
       else if(e->x()>=720 && e->x()<=800 && e->y()>=25 && e->y()<=105)
       {
           m=17;n=1;
           p=3;
           x=0;y=4;
       }
       else if(e->x()>=195 && e->x()<=275 && e->y()>=190 && e->y()<=270)
       {
           m=5;n=5;
           p=4;
           x=1;y=1;
       }
       else if(e->x()>=372 && e->x()<452 && e->y()>=190 && e->y()<270)
       {
           m=9;n=5;
           p=5;
           x=1;y=2;
       }

       else if(e->x()>=548 && e->x()<=628 && e->y()>=190 && e->y()<=270)
       {
           m=13;n=5;
           p=6;
           x=1;y=3;
       }
       else if(e->x()>=25 && e->x()<=105 && e->y()>=354 && e->y()<=434)
       {
           m=1;n=9;
           p=7;
           x=2;y=0;
       }

       else if(e->x()>=197 && e->x()<=277 && e->y()>=354 && e->y()<=434)
       {
           m=5;n=9;
           p=8;
           x=2;y=1;
       }
       else if(e->x()>=548 && e->x()<=628 && e->y()>=354 && e->y()<=434)
       {
           m=13;n=9;
           p=9;
           x=2;y=3;
       }
       else if(e->x()>=720 && e->x()<=800 && e->y()>=354 && e->y()<=434)
       {
           m=17;n=9;
           p=10;
           x=2;y=4;
       }
       else if(e->x()>=195 && e->x()<=275 && e->y()>=540 && e->y()<=620)
       {
           m=5;n=13;
           p=11;
           x=3;y=1;
       }
       else if(e->x()>=375 && e->x()<=455 && e->y()>=540 &&e->y()<=620)
       {
           m=9;n=13;
           p=12;
           x=3;y=2;
       }
       else if(e->x()>=548 && e->x()<=628 && e->y()>=540 &&e->y()<=620)
       {
           m=13;n=13;
           p=13;
           x=3;y=3;
       }
       else if(e->x()>=25 && e->x()<=105 && e->y()>=690 && e->y()<=770)
       {
           m=1;n=17;
           p=14;
           x=4;y=0;
       }
       else if(e->x()>=380 && e->x()<=460 && e->y()>=690 &&e->y()<=770)
       {
           m=9;n=17;
           p=15;
           x=4;y=2;
       }
       else if(e->x()>=720 && e->x()<=800 && e->y()>=690 &&e->y()<=770)
       {
           m=17;n=17;
           p=16;
           x=4;y=4;
       }
       else if(e->x()>=810 && e->x()<=1160 &&e->y()>=270 &&e->y()<=380)
       {
           initial();
           int i;
           count=1;
           p=17;

           show_or_hide=0;
           move_step=0;
           fly_step=0;
           switch_second_step=0;
           switch_third_step=0;
           jude_repeat_pieces=0;

           tip1->show();
           tip2->hide();
           tip3->hide();
           tip4->hide();
           tip5->hide();

           memset(map,0,19*19*sizeof(int));
           for(i=1;i<=16;i++)
           {
               mylabel[i]->hide();
           }
               return ;
       }
       else if(e->x()>=810 && e->x()<=1160 &&e->y()>=625 &&e->y()<=735)
       {
           this->close();
           initial();
           int i;
           count=1;
           memset(map,0,19*19*sizeof(int));
           for(i=1;i<=16;i++)
           {
               mylabel[i]->hide();
           }
           show_or_hide=0;
           move_step=0;
           fly_step=0;
           switch_second_step=0;
           switch_third_step=0;
           jude_repeat_pieces=0;

           tip1->show();
           tip2->hide();
           tip3->hide();
           tip4->hide();
           tip5->hide();

           return ;
       }

       else if(e->x()>=810 && e->x()<=1160 &&e->y()>=445 &&e->y()<=555)
       {
           rulegame.show();
           return;
       }
       else
           return;

      jude_single();
    emit clicked();
    }


}
