#include "online.h"

#include <QPainter>
#include <QMouseEvent>
#include <QCoreApplication>
#include <QMessageBox>
#include <QDebug>


online::online(QWidget *parent)
    : QMainWindow(parent)
{

    this->setWindowTitle("online game");
    QTextCodec::setCodecForLocale(QTextCodec::codecForLocale());
    socket=new QTcpSocket(this);
    localPoints.clear();
    this->setGeometry(360,20,800,800);

    this->setMinimumSize(800,800);
    this->setMaximumSize(800,800);


    //b=new NetGobang(this);
    initial();
    //resize(800,800);
    count=1;
    int i;
    p=1;
    show_or_hide=0;
    move_step=0;
    fly_step=0;
    switch_first_step=0;
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
        mylabel[i]->setScaledContents(1);
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


   connect(this,SIGNAL(clicked()),this,SLOT(draw_chess()));
   connect(this, SIGNAL(llocalDone(QPoint)),this, SLOT(localDone(QPoint)));
   //connect(this, SIGNAL(draw()),this, SLOT(draw_online()));
   //connect(socket, SIGNAL(readyRead()),this, SLOT(readData()));


}

online::~online()
{

}
void online::localDone(const QPoint &k)
{
    qDebug()<<"send"<<endl;
    //将数据通过socket发送到对方

    QDataStream out(socket);
    out << QChar('k');
    out << k;
    qDebug()<<k;


}
void online::readData()
{
    qDebug()<<"revice"<<isLocal<<isServer<<endl;
    emit draw();
    memset(map,0,19*19*sizeof(int));
    qDebug()<<"revice";

    //接受网络数据
    QChar c;
    QDataStream in(socket);
    in >> c;

    if(c == QChar('k'))
    {

        QPoint k;
        in >> k;
        localPoints[localPoints.count()] = k;
        for(int i = 0; i < localPoints.count(); i++)
        {
            m=localPoints[i].x();
            n=localPoints[i].y();

        }

        qDebug()<<k;

        if(m==1 && n==1)
        {
            p=1;
            x=0;y=0;
        }
        else if(m==9 && n==1)
        {
            p=2;
            x=0;y=2;
        }
        else if(m==17 && n==1)
        {
            p=3;
            x=0;y=4;
        }
        else if(m==5 && n==5)
        {
            p=4;
            x=1;y=1;
        }
        else if(m==9 && n==5)
        {
            p=5;
            x=1;y=2;
        }
        else if(m==13 && n==5)
        {
            p=6;
            x=1;y=3;
        }
        else if(m==1 && n==9)
        {
            p=7;
            x=2;y=0;
        }
        else if(m==5 && n==9)
        {
            p=8;
            x=2;y=1;
        }
        else if(m==13 && n==9)
        {
            p=9;
            x=2;y=3;
        }
        else if(m==17 && n==9)
        {
            p=10;
            x=2;y=4;
        }
        else if(m==5 && n==13)
        {
            p=11;
            x=3;y=1;
        }
        else if(m==9 && n==13)
        {
            p=12;
            x=3;y=2;
        }
        else if(m==13 && n==13)
        {
            p=13;
            x=3;y=3;
        }
        else if(m==1 && n==17)
        {
            p=14;
            x=4;y=0;
        }
        else if(m==9 && n==17)
        {
            p=15;
            x=4;y=2;
        }
        else if(m==17 && n==17)
        {
            p=16;
            x=4;y=4;
        }

        jude_single();
        draw_online();

        //将坐标发送给棋盘
        //此处添加
        //board->棋盘
    }
}
void online::start(bool s)
{
    isLocal = s;
    isServer = s;
}
void online::startGame(QTcpSocket *s, bool isServer)
{
    socket = s;
    connect(socket, SIGNAL(readyRead()),this, SLOT(readData()));
    start(isServer);

}

void online::draw_online()
{
    qDebug()<<"draw_online"<<isLocal<<isServer<<endl;
    int i,j;
    for(i=0;i<19;i++)
    {
        for(j=0;j<19;j++)
        {
            if(map[i][j]==1)
            {
                QPixmap chess1;
                chess1.load(":/pic/black.png");
                mylabel[p]->setPixmap(chess1);

                if(show_or_hide==0)
                {
                    mylabel[p]->show();
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
                mylabel[p]->setPixmap(chess2);

                if(show_or_hide==0)
                {
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
}

void online::initial(void)
{
    int i,j;
    board.three_num=0;
    board.fly_num=0;
    board.temp_num=0;
    board.black_num=0;
    board.white_num=0;
    board.temp_x=0;
    board.temp_y=0;
    board.temp_second_x=0;
    board.temp_second_y=0;
    board.colour_piece=' ';
    for(i=0;i<8;i++)
    {
        for(j=0;j<8;j++)
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

    return;
}

void online::System(int &jude)
{

   if(jude==1)
    {
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
    return;
}

void online::White(void)
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
    return;
}

void online::Black(void)
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
    return;
}

void online::click_pieces(char &colour)
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
    return;
}

void online::move_pieces(char &colour)
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

    if((board.white_num==3 || board.black_num==3) && board.temp_num==12 )       //判断是否有进入第三阶段的,如果存在，下一回合为飞子阶段
    {
       switch_third_step=1;
       fly_step=0;
    }
    return;
}

void online::fly_pieces(char &colour)
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

    if(switch_second_step==1)         //如果还有一方是第二阶段的，那下一回合就关闭第三阶段的判断
    {
        switch_third_step=0;
    }
        /*if(board.fly_num==6)                      //设计窗口,此时跳出对话框，询问是否和棋
         {
             printf("和棋！是否同意? (0)同意  (1)不同意");
             scanf("%d",&i);
             board.fly_num=0;                   //**
         }*/
    return;
}
void online::eat_pieces(char &colour)
{
    if(eat_or_not()==1)
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
         jude_repeat_pieces2=1;      // !!**
         return;
     }
     if((board.white_num==3 || board.black_num==3) && board.temp_num==12 && switch_first_step==0)   //**    //判断是否有进入第三阶段的,switch_first_step为刚下完六子并吃剩三子的情况，不会打开第三阶段的开关
     {
        if(jude_repeat_pieces2==0)          // !!**  //两个开关（jude_repeat_pieces），防止只有三子方第三次吃子后又进入飞子阶段
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

int online::eat_or_not()
{
    int i,j,jude=0;

      if(board.three_num==2 || board.three_num==3)                                    //判断双方都为磨坊的情况
       {
            for(i=0;i<5;i++)
            {
                for(j=0;j<5;j++)
                {
                    if(board.chess_board[i][j]=='2' || board.chess_board[i][j]=='1')
                        jude++;
                }
            }
        }

        i=x;
        j=y;
        if(board.chess_board[i][j]=='#' || board.chess_board[i][j]==' ')
        {
            return 1;
        }
        if(i==0 || i==4 || (i==0 && j==2) || (i==4 && j==2))
        {
            j=0;
            if(board.chess_board[i][j]==board.chess_board[i][j+2] && board.chess_board[i][j]==board.chess_board[i][j+4] && board.chess_board[i][j+2]==board.chess_board[i][j+4])
            {
                return 1;
            }
        }
        else if(i==1 || i==3 || (i==1 && j==2) || (i==3 && j==2))
        {
            j=1;
            if(board.chess_board[i][j]==board.chess_board[i][j+1] && board.chess_board[i][j]==board.chess_board[i][j+2] && board.chess_board[i][j+1]==board.chess_board[i][j+2])
            {
                return 1;
            }
        }
        i=x;
        j=y;
        if(j==0 || j==4 || (j==0 && i==2) || (j==4 && i==2))
        {
            i=0;
            if(board.chess_board[i][j]==board.chess_board[i+2][j] && board.chess_board[i][j]==board.chess_board[i+4][j] && board.chess_board[i+2][j]==board.chess_board[i+4][j])
            {
                return 1;
            }
        }
        else if(j==1 || j==3 || (j==1 && i==2) || (j==3 && i==2))
        {
            i=1;
            if(board.chess_board[i][j]==board.chess_board[i+1][j] && board.chess_board[i][j]==board.chess_board[i+2][j] && board.chess_board[i+1][j]==board.chess_board[i+2][j])
            {
                return 1;
            }
        }
        if(jude==6 || jude==8 || jude==10)                          // !!**
            return 0;
        return 0;
}

int online::jude_three(void)
{
    int i,j,jude=0;
    board.three_num=0;              // !! ***

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

int online::jude_move_up()
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
    else
    {
        return 0;
    }
}

int online::jude_move_down()
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

void online::jude_result_near_pieces(char &colour_piece)
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
            if(board.chess_board[i][j]=='#' || board.chess_board[i][j]==' ' )   // !!**        //判断棋盘数组，不为可落子点 或 无子，则跳过
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
                   QString str,str2,s;
                   str2=board.colour_piece;
                   str="围死";
                   s=colour;
                   cout.flush();
                   cout<<str<<endl
                         <<str2<<endl
                           <<"*"<<s<<endl;

                   if(colour=='2')                   //设计窗口
                   {

                       d_w_win.show();

                   }
                   else if(colour=='1')
                   {

                       d_b_win.show();

                   }
    return;
}

void online::jude_bug(int &step,int &jude)
{
    if((step==0 || step==1) && (board.chess_board[x][y]==board.colour_piece || board.chess_board[x][y]=='#'))
    {
        if(step==1 && board.chess_board[x][y]==board.colour_piece && board.temp_second_x==x && board.temp_second_y)        //如果第二阶段起子返回 ，则颜色还为上一色，仍继续进入
        {               QTextStream cout(stdout,QIODevice::WriteOnly);
                        QString str;
                        str="起子返回";
                        cout.flush();
                        cout<<str<<endl;
            System(jude);
            return;
        }
        if(board.chess_board[x][y]==board.colour_piece)
        {
                            QTextStream cout(stdout,QIODevice::WriteOnly);
                        QString s,b;
                        b=board.colour_piece;
                        s="误点";
                        cout.flush();
                        cout<<s<<endl<<b<<endl;
              return;
        }

    }
    else if(board.chess_board[x][y]=='#' && x==board.temp_second_x && y==board.temp_second_y)         //当子没进行移动 落回原点的话 ，落子阶段能正常进行
    {
        /*QTextStream cout(stdout,QIODevice::WriteOnly);
                       int str,str2;
                       str=board.temp_x;
                       str2=board.temp_y;
                       cout.flush();
                       cout<<str<<endl
                             <<str2<<endl;*/
        System(jude);
        return;
    }
    else if(step==2 && (board.chess_board[x][y]!='#'))
    {
        return;
    }
    else
    {
        System(jude);
        return;
    }
}

void online::jude_single(void)
{
    int jude=0;

    if(board.temp_num>=5)                       //当总落子数为5颗以上才会 判断工厂
        jude=jude_three();
    if(jude==0)
    {
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
                 return;
            }
        }
    }
    else if(jude==1)
    {
        //isLocal=true;
        if(board.chess_board[x][y]==board.colour_piece || board.chess_board[x][y]=='#')
        {
            QTextStream cout(stdout,QIODevice::WriteOnly);
                    QString s;
                    s="吃子误点";
                    cout.flush();
                    cout<<s<<endl;
            return;
        }
        else
        {
              System(jude);
              return;
        }
    }
}

void online::jude_win_num_pieces(void)
{
    QTextCodec::setCodecForLocale(QTextCodec::codecForLocale());

    QTextStream cout(stdout,QIODevice::WriteOnly);
    QString str;

    if(board.black_num<=2)                      //设计弹出窗口，询问退出 或 开始下一盘
    {
        w_win.show();
    }
    else if(board.white_num<=2)
    {
        b_win.show();
    }
}

void online::draw_chess()
{
    QPoint k;
    int i,j;

    for(i=0;i<19;i++)
    {
        for(j=0;j<19;j++)
        {
            if(map[i][j]==1)
            {
                QPixmap chess1;
                chess1.load(":/pic/black.png");
                mylabel[p]->setPixmap(chess1);

                if(show_or_hide==0)
                {
                    mylabel[p]->show();
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
                mylabel[p]->setPixmap(chess2);

                if(show_or_hide==0)
                {
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


    k=QPoint(m,n);
    emit llocalDone(k);

}

void online::mousePressEvent(QMouseEvent *e)
{

    memset(map,0,19*19*sizeof(int));

    if(e->x()>=0&&e->x()<=760&&e->y()>=0&&e->y()<=760)
    {
        if(e->x()>=0 && e->x()<=120 && e->y()>=0 && e->y()<=120)
        {
            m=1;n=1;
        }
        else if(e->x()>=320 && e->x()<=440 && e->y()>=0&&e->y()<=120)
        {
            m=9;n=1;
        }
        else if(e->x()>=640 && e->x()<=760 && e->y()>=0 && e->y()<=120)
        {
            m=17;n=1;
           // p=3;
         //   x=0;y=4;
        }
        else if(e->x()>=160 && e->x()<=280 && e->y()>=160 && e->y()<=280)
        {
            m=5;n=5;
          //  p=4;
          //  x=1;y=1;
        }
        else if(e->x()>=320 && e->x()<440 && e->y()>=160 && e->y()<280)
        {
            m=9;n=5;
        //    p=5;
         //   x=1;y=2;
        }
        else if(e->x()>=480 && e->x()<=600 && e->y()>=160 && e->y()<=280)
        {
            m=13;n=5;
          //  p=6;
          //  x=1;y=3;
        }
        else if(e->x()>=0 && e->x()<=120 && e->y()>=320 && e->y()<=440)
        {
            m=1;n=9;
          //  p=7;
          //  x=2;y=0;
        }
        else if(e->x()>=160 && e->x()<=280 && e->y()>=320 && e->y()<=440)
        {
            m=5;n=9;
         //   p=8;
         //   x=2;y=1;
        }
        else if(e->x()>=480 && e->x()<=600 && e->y()>=320 && e->y()<=440)
        {
            m=13;n=9;
        //    p=9;
         //   x=2;y=3;
        }
        else if(e->x()>=640 && e->x()<=760 && e->y()>=320 && e->y()<=440)
        {
            m=17;n=9;
       //     p=10;
        //    x=2;y=4;
        }
        else if(e->x()>=160 && e->x()<=280 && e->y()>=480 && e->y()<=600)
        {
            m=5;n=13;
        //    p=11;
        //    x=3;y=1;
        }
        else if(e->x()>=320 && e->x()<=440 && e->y()>=480 &&e->y()<=600)
        {
            m=9;n=13;

        }
        else if(e->x()>=480 && e->x()<=600 && e->y()>=480 &&e->y()<=600)
        {
            m=13;n=13;
        }
        else if(e->x()>=0 && e->x()<=120 && e->y()>=640 && e->y()<=760)
        {
            m=1;n=17;
        }
        else if(e->x()>=320 && e->x()<=440 && e->y()>=640 &&e->y()<=760)
        {
            m=9;n=17;
        }
        else if(e->x()>=640 && e->x()<=760 && e->y()>=640 &&e->y()<=760)
        {
            m=17;n=17;
        }
        else
            return;



        if(m==1 && n==1)
        {
            p=1;
            x=0;y=0;
        }
        else if(m==9 && n==1)
        {
            p=2;
            x=0;y=2;
        }
        else if(m==17 && n==1)
        {
            p=3;
            x=0;y=4;
        }
        else if(m==5 && n==5)
        {
            p=4;
            x=1;y=1;
        }
        else if(m==9 && n==5)
        {
            p=5;
            x=1;y=2;
        }
        else if(m==13 && n==5)
        {
            p=6;
            x=1;y=3;
        }
        else if(m==1 && n==9)
        {
            p=7;
            x=2;y=0;
        }
        else if(m==5 && n==9)
        {
            p=8;
            x=2;y=1;
        }
        else if(m==13 && n==9)
        {
            p=9;
            x=2;y=3;
        }
        else if(m==17 && n==9)
        {
            p=10;
            x=2;y=4;
        }
        else if(m==5 && n==13)
        {
            p=11;
            x=3;y=1;
        }
        else if(m==9 && n==13)
        {
            p=12;
            x=3;y=2;
        }
        else if(m==13 && n==13)
        {
            p=13;
            x=3;y=3;
        }
        else if(m==1 && n==17)
        {
            p=14;
            x=4;y=0;
        }
        else if(m==9 && n==17)
        {
            p=15;
            x=4;y=2;
        }
        else if(m==17 && n==17)
        {
            p=16;
            x=4;y=4;
        }
        else
            return;
        jude_single();

       emit clicked();

}
}



