#include "mainwindow.h"

#include <QApplication>
#include "Gamecontroller.h"

GameController* game = nullptr;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    game = new GameController(&a);
    MainWindow w;
    w.show();
    return a.exec();
    delete game;
}
