#ifndef BOARD_H
#define BOARD_H

#include <QString>

const int row = 10,col = 9;

class Board{
public:
    int** board; //row:1~10 col:1~9

public:
    Board();
    ~Board();
    QString getName(int x,int y); //获取board[x][y]处的棋子名
    static int boardToWindowY(int x);// 注意board和窗口x、y相反
    static int boardToWindowX(int y);

};

#endif // BOARD_H
