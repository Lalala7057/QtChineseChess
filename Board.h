#ifndef BOARD_H
#define BOARD_H

#include <QString>
#include <QDebug>
const int row = 10,col = 9;

class Board{
public:
    int** board; //row:1~10 col:1~9

public:
    Board();
    ~Board();
    QString getName(int x,int y); //获取board[x][y]处的棋子名
    int boardToWindowY(int x);// 注意board和窗口x、y相反
    int boardToWindowX(int y);
    void MoveBoard(int x1,int y1,int x2,int y2);
    bool isValidMove(int,int,int,int);

};

#endif // BOARD_H
