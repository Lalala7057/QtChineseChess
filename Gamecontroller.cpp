#include "Gamecontroller.h"

GameController::GameController() {
    this->curBoard = new Board();
}
GameController::~GameController() {
    delete this->curBoard;
}
GameController::GameController(QObject *parent){
    this->curBoard = new Board();
}
