#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <QObject>
#include <QStack>

#include "Board.h"

class GameController: public QObject
{
public:
    Board* curBoard;
    // struct Recorder{
    //     ChessPiece::NAME _name;
    //     ChessPiece::Point _origin,_end;
    //     Recorder(){};
    //     Recorder(ChessPiece::NAME name,ChessPiece::Point origin,ChessPiece::Point end);
    // };
    // bool _isWin;
    // bool _isRedTurn;
    // int _round;
    // QStack<Recorder> recorder; //记录行棋，便于悔棋
    explicit GameController(QObject *parent = nullptr);
    GameController();
    ~GameController();
};
extern GameController *game;

#endif // GAMECONTROLLER_H
