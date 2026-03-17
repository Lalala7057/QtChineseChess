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
    board[1][1] = board[1][9] = -1;
    board[1][2] = board[1][8] = -2;
    board[1][3] = board[1][7] = -3;
    board[1][4] = board[1][6] = -4;
    board[1][5] = -5;
    board[3][2] = board[3][8] = -6;
    board[4][1] = board[4][3] = board[4][5] = board[4][7] = board[4][9] = -7;
    board[10][1] = board[10][9] = 1;
    board[10][2] = board[10][8] = 2;
    board[10][3] = board[10][7] = 3;
    board[10][4] = board[10][6] = 4;
    board[10][5] = 5;
    board[8][2] = board[8][8] = 6;
    board[7][1] = board[7][3] = board[7][5] = board[7][7] = board[7][9] = 7;
}

Board::~Board(){
    for(int i = 0;i <= row;i++)
    {
        delete [] board[i];
    }
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
void Board::MoveBoard(int x1,int y1,int x2,int y2){
    int val = board[x1][y1];
    board[x2][y2] = val;
    board[x1][y1] = 0;
}
bool Board::isValidMove(bool isRedTurn,int x1,int y1,int x2,int y2){
    const int val = board[x1][y1];
    if(val == 0) return false;
    //  1. 通用判断
    //超出棋盘
    if(x1 < 1 || x2 < 1 || x1 > 10 || x2 > 10 || y1 < 1 || y2 < 1 || y1 > 9 || y2 > 9){
        qDebug("移动超出棋盘");
        return false;
    }
    // 移动棋子不对
    if((isRedTurn && (val < 0))||(!isRedTurn && (val > 0))) {
        qDebug()<<"走了对方的棋！";
        return false;
    }
    // 目标位置有自己棋子
    if((isRedTurn && (board[x2][y2] > 0))|| (!isRedTurn && (board[x2][y2] < 0)))
    {
        qDebug("目标位置有自己棋子");
        return false;
    }

    //  2. 各棋子走法判断
    switch(val){
    case 1:case -1:{
        if((x1 == x2 && y1 == y2)||(x1 != x2 && y1 != y2)) return false;
        if(x1 < x2){
            for(int i = x1 + 1;i < x2;i++){
                if(board[i][y1] != 0) {qDebug()<<"車前进有阻挡";return false;}
            }
        }
        else if(x1 > x2){
            for(int i = x1 - 1;i > x2;i--){
                if(board[i][y1] != 0) {qDebug()<<"車前进有阻挡";return false;}
            }
        }
        else if(y1 < y2){
            for(int i = y1 + 1;i < y2;i++){
                if(board[x1][i] != 0) {qDebug()<<"車前进有阻挡";return false;}
            }
        }
        else{
            for(int i = y1 - 1;i > y2;i--){
                if(board[x1][i] != 0) {qDebug()<<"車前进有阻挡";return false;}
            }
        }
        return true;
    }
    case 2:case -2:{
        bool flag = true;
        if(!((abs(x1-x2) == 2 && abs(y1-y2) == 1) || (abs(y1-y2) == 2 && abs(x1-x2) == 1))) return false;
        if(x1-x2 == 2){
            if(board[x1-1][y1] != 0) flag = false;
        }
        else if(x2-x1 == 2){
            if(board[x1+1][y1] != 0) flag = false;
        }
        else if(y1-y2 == 2){
            if(board[x1][y1-1] != 0) flag = false;
        }
        else if(y2-y1 == 2){
            if(board[x1][y1+1] != 0) flag = false;
        }
        if(!flag) qDebug()<<"别住马腿";
        return flag;
    }
    case 3:case -3:{
        if(!(abs(x1-x2)==2 && abs(y1-y2)==2)) return false;
        if(val == 3 && x2 < 6) return false;
        if(val == -3 && x2 > 5) return false;
        return true;
    }
    case 4:case -4:{
        if(y2 < 4 || y2 > 6 || (x2 > 3 && x2 < 8)) return false;
        if(!(abs(x1-x2)==1&&abs(y1-y2) == 1)) return false;
        return true;
    }
    case 5:case -5:{
        if(!((abs(x1-x2)==1&&abs(y1-y2)==0)|| (abs(x1-x2)==0&&abs(y1-y2)==1))) return false;
        if(y2 > 6 || y2 < 4 || (x2 > 3 && x2 < 8)) return false;
        return true;
    }
    case 7:{
        if(x1 - x2 == 1 && y2 - y1 == 0) return true;
        if(x1 < 6 && x1-x2 == 0 && abs(y2-y1) == 1) return true;
        return false;
    }
    case -7:{
        if(x2 - x1 == 1 && y2 - y1 == 0) return true;
        if(x1 > 5 && x1-x2 == 0 && abs(y2-y1) == 1) return true;
        return false;
    }
    case 6:case -6:{
        if((x1 == x2 && y1 == y2)||(x1 != x2 && y1 != y2)) return false;
        int count = 0;
        if(x1 < x2){
            for(int i = x1 + 1;i < x2;i++){
                if(board[i][y1] != 0) count++;
            }
        }
        else if(x1 > x2){
            for(int i = x1 - 1;i > x2;i--){
                if(board[i][y1] != 0) count++;
            }
        }
        else if(y1 < y2){
            for(int i = y1 + 1;i < y2;i++){
                if(board[x1][i] != 0) count++;
            }
        }
        else{
            for(int i = y1 - 1;i > y2;i--){
                if(board[x1][i] != 0) count++;
            }
        }
        if(board[x2][y2] == 0 && count == 0) return true;
        if((count == 0 && board[x2][y2] * val > 0)|| (count == 1 && board[x2][y2] * val < 0)) return true;
        else return false;
    }
    default:return false;
    }
}

