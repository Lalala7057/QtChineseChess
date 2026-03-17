#include "GameController.h"
#include <QPainter>
#include <QMouseEvent>
GameController::~GameController() {
    delete this->curBoard;
}
GameController::GameController(QObject *parent){
    this->curBoard = new Board();
    this->curWindow = new MainWindow(nullptr,curBoard);
    isRedTurn = true;
    connect(curWindow, &MainWindow::boardClicked,this, &GameController::onBoardClicked);
}

void GameController::Move(int x1,int y1,int x2,int y2){
    if(curBoard->isValidMove(x1,y1,x2,y2))
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
    int val = curBoard->board[boardX][boardY];
    Move(8,2,1,2);
    /* 这里编写鼠标控制走棋 */
}



