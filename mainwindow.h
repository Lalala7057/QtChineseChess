#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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
    ~MainWindow();

protected:
    void paintEvent(QPaintEvent* event);

private:
    Ui::MainWindow *ui;
    void initBoard();
    void initPieces();
    void drawBoard(QPainter& painter);
    void drawPieces(QPainter& painter);
    void drawPiece(QPainter& painter,int,int);
    void erasePiece(QPainter& painter,int,int);
};
#endif // MAINWINDOW_H
