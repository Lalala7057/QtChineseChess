#include "GameController.h"
#include <QPainter>
#include <QMouseEvent>

GameController::~GameController() {
    for(int i = 0;i <= row;i++)
    {
        delete this->curBoard->board[i];
    }
    delete curBoard;
    delete curWindow;
}
GameController::GameController(QObject *parent){
    this->curBoard = new Board();
    this->curWindow = new MainWindow(nullptr,curBoard);
    isRedTurn = true;
    connect(curWindow, &MainWindow::boardClicked,this, &GameController::onBoardClicked);
}

void GameController::Move(int x1,int y1,int x2,int y2){
    if(curBoard->isValidMove(isRedTurn,x1,y1,x2,y2))
    {
        curBoard->MoveBoard(x1,y1,x2,y2);
        QPainter painter(&curWindow->piecesCache);
        curWindow->drawPiece(painter,x2,y2);
        curWindow->erasePiece(painter,x1,y1);
        isRedTurn = !isRedTurn;
        qDebug("(%d,%d)处棋子已移动",x1,y1);
    }
    else qDebug("非法走棋");
}
void GameController::onBoardClicked(int boardX, int boardY){
    static bool isSelected = false;
    static int preX = boardX,preY = boardY;
    int val = curBoard->board[boardX][boardY];
    if(!isSelected){
        if(val != 0){
            //选中标记
            preX = boardX,preY = boardY;
            QPainter painter(&curWindow->piecesCache);
            curWindow->markPiece(painter,boardX,boardY);
            isSelected = true;
        }
    }
    else{
        // curWindow->erasePiece(painter,preX,preY);
        if(!curBoard->isValidMove(isRedTurn,preX,preY,boardX,boardY)){
            QPainter painter(&curWindow->piecesCache);
            curWindow->eraseMark(painter,preX,preY);
        }
        Move(preX,preY,boardX,boardY);
        isSelected = false;
    }
    /* 这里编写鼠标控制走棋 */
}



