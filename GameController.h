#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <QObject>
#include <QStack>

#include "Board.h"
#include "MainWindow.h"


class GameController: public QObject
{
private:
    struct Information{ //val从(x1,y1)到(x2,y2)
        int val;
        int x1,y1,x2,y2;
        Information(){}
        Information(int v,int X1,int Y1,int X2,int Y2){
            val=v;
            x1=X1,y1=Y1,x2=X2,y2=Y2;
        }
    };
public:
    Board* curBoard;
    MainWindow* curWindow;

    QStack<Information> recorder;   //行棋记录
    bool isRedTurn;

    explicit GameController(QObject *parent = nullptr);
    ~GameController();
    void Move(int,int,int,int);
    bool windowToBoard(int winX, int winY, int& boardX, int& boardY);

private slots:
    void onBoardClicked(int boardX, int boardY);  // 处理棋盘点击


};

#endif // GAMECONTROLLER_H
