#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Board.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    //棋盘储存在boardCache，棋子层在piecesCache，重绘过程在内部完成
    QPixmap boardCache;
    QPixmap piecesCache;
    MainWindow(QWidget *parent = nullptr);
    MainWindow(QWidget* parent = nullptr,Board* board = nullptr);
    ~MainWindow();
    void drawPiece(QPainter& painter,int,int);
    void erasePiece(QPainter& painter,int,int);
    void markPiece(QPainter& painter,int,int);
    void eraseMark(QPainter& painter,int x,int y);

protected:
    void paintEvent(QPaintEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;

private:
    Ui::MainWindow *ui;
    Board* board;
    bool isInitialized;
    void initBoard();
    void initPieces();
    void drawBoard(QPainter& painter);
    void drawPieces(QPainter& painter);
    bool windowToBoard(int winX, int winY, int& boardX, int& boardY);

signals:
    void boardClicked(int boardX, int boardY);
};
#endif // MAINWINDOW_H
