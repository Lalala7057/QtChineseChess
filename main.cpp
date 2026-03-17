#include <QApplication>
#include "GameController.h"

GameController* game = nullptr;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    game = new GameController(&a);
    game->curWindow->show();
    return a.exec();
}
