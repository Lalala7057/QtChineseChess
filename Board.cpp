#include "Board.h"

Board::Board() {
    board = new int*[row + 1];
    for(int i = 0;i<= row;i++) {
        board[i] = new int[col+1];
    }
    for(int i = 0;i<= row;i++){
        for(int j = 0;j<=col;j++) {
            board[i][j] = 0;
        }
    }
    board[1][1] = board[1][9] = 1;
    board[1][2] = board[1][8] = 2;
    board[1][3] = board[1][7] = 3;
    board[1][4] = board[1][6] = 4;
    board[1][5] = 5;
    board[3][2] = board[3][8] = 6;
    board[4][1] = board[4][3] = board[4][5] = board[4][7] = board[4][9] = 7;
    board[10][1] = board[10][9] = -1;
    board[10][2] = board[10][8] = -2;
    board[10][3] = board[10][7] = -3;
    board[10][4] = board[10][6] = -4;
    board[10][5] = -5;
    board[8][2] = board[8][8] = -6;
    board[7][1] = board[7][3] = board[7][5] = board[7][7] = board[7][9] = -7;
}

Board::~Board(){
    delete board;
}
int Board::boardToWindowY(int x){
    if(x<1 || x>10) {qDebug("x->Y转换有误");return -1;}
    const int StartPosY = 40,meshSize = 60;
    return StartPosY + (x-1)*meshSize;
}
int Board::boardToWindowX(int y){
    if(y<1 || y>9) {qDebug("y->X转换有误");return -1;}
    const int StartPosX = 80,meshSize = 60;
    return StartPosX + (y-1)*meshSize;
}
QString Board::getName(int x,int y){
    switch(board[x][y])
    {
        case 0:return "";
        case 1:case -1:return "車";
        case 2:case -2:return "馬";
        case 3:return "相";case -3:return "象";
        case 4:return "仕";case -4:return "士";
        case 5:return "帅";case -5:return "将";
        case 6:case -6:return "炮";
        case 7:return "兵";case -7:return "卒";
        default:
        {
            qDebug("x=%d,y=%d,找不到board[x][y]处的棋子",x,y);
            return "";
        }
    }

}
