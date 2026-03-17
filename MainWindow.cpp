#include "MainWindow.h"
#include "ui_MainWindow.h"

#include<QPainter>
#include<QPaintEvent>

extern const int row,col;

const int StartPosX = 80,StartPosY = 40,windowWidth = 1920,windowHeight = 1080;
const int meshSize = 60,radius =25; //网格、棋子大小

MainWindow::MainWindow(QWidget *parent,Board * board): QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);
    isInitialized = false;
    this->board = board;
    setGeometry(StartPosX,StartPosY,windowWidth,windowHeight);
    setMinimumSize(800,600);
    setMaximumSize(1200,900);
    resize(800,600);
    setWindowTitle("中国象棋");
}
void MainWindow::initBoard(){
    if(!boardCache){
        qreal dpr = devicePixelRatioF();  // 获取屏幕缩放比例
        boardCache = QPixmap(size() * dpr);
        boardCache.setDevicePixelRatio(dpr);  // 关键：设置像素比
        boardCache.fill(Qt::transparent);
        QPainter p(&boardCache);
        p.setRenderHint(QPainter::Antialiasing, true);        // 抗锯齿
        p.setRenderHint(QPainter::TextAntialiasing, true);    // 文字抗锯齿
        p.setRenderHint(QPainter::SmoothPixmapTransform, true);
        drawBoard(p);
    }
}
void MainWindow::initPieces(){
    if(!piecesCache){
        qreal dpr = devicePixelRatioF();  // 获取屏幕缩放比例
        piecesCache = QPixmap(size() * dpr);
        piecesCache.setDevicePixelRatio(dpr);  // 关键：设置像素比
        piecesCache.fill(Qt::transparent);
        QPainter p(&piecesCache);
        p.setRenderHint(QPainter::Antialiasing, true);        // 抗锯齿
        p.setRenderHint(QPainter::TextAntialiasing, true);    // 文字抗锯齿
        p.setRenderHint(QPainter::SmoothPixmapTransform, true);
        drawPieces(p);
    }
}
void MainWindow::paintEvent(QPaintEvent* event){
    if(!isInitialized){
        initBoard();
        initPieces();
        isInitialized = true;
    }
    QPainter painter(this);
    painter.drawPixmap(0,0,boardCache);
    painter.drawPixmap(0,0,piecesCache);
    event->accept();
}
void MainWindow::drawPieces(QPainter& painter){
    for(int i = 1;i <= 10;i++){
        for(int j = 1;j <= 9;j++){
            drawPiece(painter,i,j);
        }
    }
}
void MainWindow::drawBoard(QPainter& painter){
    painter.setRenderHint(QPainter::Antialiasing);
    QPen pen(Qt::black,Qt::SolidLine);
    pen.setWidth(3);
    painter.setPen(pen);
    //---主体（注意窗口：向右为X正向，向下为Y正向---//
    const int boardWidth = meshSize * (col-1),boardHeight = meshSize * (row-1);
    for(int i = 1;i <= col;i++)
    {
        int curX = StartPosX + (i-1)* meshSize;
        if(i == 1 || i == col)  painter.drawLine(curX,StartPosY,curX,StartPosY+boardHeight);
        else{
            painter.drawLine(curX,StartPosY,curX,StartPosY+4*meshSize);
            painter.drawLine(curX,StartPosY+5*meshSize,curX,StartPosY+boardHeight);
        }
    }
    for(int i = 1;i <= row;i++)
    {
        int curY = StartPosY + (i-1)* meshSize;
        painter.drawLine(StartPosX,curY,StartPosX+boardWidth,curY);
    }
    //---九宫格---//
    {
        int startX = StartPosX + meshSize * 3,endX = startX + meshSize * 2;
        painter.drawLine(startX,StartPosY,endX,StartPosY+2*meshSize);
        painter.drawLine(startX,StartPosY+2*meshSize,endX,StartPosY);
        painter.drawLine(startX,StartPosY+7*meshSize,endX,StartPosY+boardHeight);
        painter.drawLine(startX,StartPosY+boardHeight,endX,StartPosY+7*meshSize);
    }
    //---十字---//
    {
        pen.setWidth(2);
        painter.setPen(pen);
        int border = 4,len = 5;
        //  卒林线
        // 一象限
        for(int i = 0;i < 4;i++){
            int startX = StartPosX+border+i*2*meshSize,startY = StartPosY + meshSize*3 - border - len;
            QVector<QPoint> points = {
                QPoint(startX,startY),
                QPoint(startX,startY + len),
                QPoint(startX+len,startY + len)
            };
            painter.drawPolyline(points);
        }
        for(int i = 0;i < 4;i++) {
            int startX = StartPosX+border+i*2*meshSize,startY = StartPosY + meshSize*6 - border - len;
            QVector<QPoint> points = {
                QPoint(startX,startY),
                QPoint(startX,startY + len),
                QPoint(startX+len,startY + len)
            };
            painter.drawPolyline(points);
        }
        //四象限
        for(int i = 0;i < 4;i++){
            int startX = StartPosX+border+i*2*meshSize,startY = StartPosY + meshSize*3 + border + len;
            QVector<QPoint> points = {
                QPoint(startX,startY),
                QPoint(startX,startY - len),
                QPoint(startX+len,startY - len)
            };
            painter.drawPolyline(points);
        }
        for(int i = 0;i < 4;i++) {
            int startX = StartPosX+border+i*2*meshSize,startY = StartPosY + meshSize*6 +border + len;
            QVector<QPoint> points = {
                QPoint(startX,startY),
                QPoint(startX,startY - len),
                QPoint(startX+len,startY -len)
            };
            painter.drawPolyline(points);
        }
        //二象限
        for(int i = 1;i < 5;i++){
            int startX = StartPosX-border+i*2*meshSize,startY = StartPosY + meshSize*3 - border - len;
            QVector<QPoint> points = {
                QPoint(startX,startY),
                QPoint(startX,startY + len),
                QPoint(startX - len,startY + len)
            };
            painter.drawPolyline(points);
        }
        for(int i = 1;i < 5;i++) {
            int startX = StartPosX-border+i*2*meshSize,startY = StartPosY + meshSize*6 - border - len;
            QVector<QPoint> points = {
                QPoint(startX,startY),
                QPoint(startX,startY + len),
                QPoint(startX - len,startY + len)
            };
            painter.drawPolyline(points);
        }
        //三象限
        for(int i = 1;i < 5;i++){
            int startX = StartPosX-border+i*2*meshSize,startY = StartPosY + meshSize*3 + border + len;
            QVector<QPoint> points = {
                QPoint(startX,startY),
                QPoint(startX,startY - len),
                QPoint(startX - len,startY - len)
            };
            painter.drawPolyline(points);
        }
        for(int i = 1;i < 5;i++) {
            int startX = StartPosX-border+i*2*meshSize,startY = StartPosY + meshSize*6 + border + len;
            QVector<QPoint> points = {
                QPoint(startX,startY),
                QPoint(startX,startY - len),
                QPoint(startX - len,startY - len)
            };
            painter.drawPolyline(points);
        }
        //  炮位
        //一象限
        for(int i = 0;i < 2;i++) {
            int startX = StartPosX+meshSize+border+i*6*meshSize,startY = StartPosY + meshSize*2 - border - len;
            QVector<QPoint> points = {
                QPoint(startX,startY),
                QPoint(startX,startY + len),
                QPoint(startX + len,startY + len)
            };
            painter.drawPolyline(points);
            startY = startY + 5*meshSize;
            points = {
                QPoint(startX,startY),
                QPoint(startX,startY + len),
                QPoint(startX + len,startY + len)
            };
            painter.drawPolyline(points);
        }
        //四象限
        for(int i = 0;i < 2;i++) {
            int startX = StartPosX+meshSize+border+i*6*meshSize,startY = StartPosY + meshSize*2 + border + len;
            QVector<QPoint> points = {
                QPoint(startX,startY),
                QPoint(startX,startY - len),
                QPoint(startX + len,startY - len)
            };
            painter.drawPolyline(points);
            startY = startY + 5*meshSize;
            points = {
                QPoint(startX,startY),
                QPoint(startX,startY - len),
                QPoint(startX + len,startY - len)
            };
            painter.drawPolyline(points);
        }
        //二象限
        for(int i = 0;i < 2;i++) {
            int startX = StartPosX+meshSize-border+i*6*meshSize,startY = StartPosY + meshSize*2 - border - len;
            QVector<QPoint> points = {
                QPoint(startX,startY),
                QPoint(startX,startY + len),
                QPoint(startX - len,startY + len)
            };
            painter.drawPolyline(points);
            startY = startY + 5*meshSize;
            points = {
                QPoint(startX,startY),
                QPoint(startX,startY + len),
                QPoint(startX - len,startY + len)
            };
            painter.drawPolyline(points);
        }
        //三象限
        for(int i = 0;i < 2;i++) {
            int startX = StartPosX+meshSize-border+i*6*meshSize,startY = StartPosY + meshSize*2 + border + len;
            QVector<QPoint> points = {
                QPoint(startX,startY),
                QPoint(startX,startY - len),
                QPoint(startX - len,startY - len)
            };
            painter.drawPolyline(points);
            startY = startY + 5*meshSize;
            points = {
                QPoint(startX,startY),
                QPoint(startX,startY - len),
                QPoint(startX - len,startY - len)
            };
            painter.drawPolyline(points);
        }
    }
    //加深边框
    {
        pen.setWidth(8);
        pen.setJoinStyle(Qt::RoundJoin);
        painter.setPen(pen);
        painter.drawRect(StartPosX - 10,StartPosY - 10,boardWidth + 20,boardHeight + 20);
    }
    //楚河汉界
    {
        QFont font("楷体",35,QFont::Bold);
        int margin = 5;
        int startX = StartPosX + meshSize,startY = StartPosY + 4*meshSize+margin;
        int wid = 2*meshSize,hei = meshSize-margin;
        QRect rect1(startX,startY,wid,hei);
        QRect rect2(startX+meshSize*4,startY,wid,hei);
        painter.setPen(QPen(Qt::black,10));
        painter.setFont(font);
        painter.drawText(rect1, Qt::AlignCenter,"楚河");
        painter.drawText(rect2, Qt::AlignCenter,"汉界");
    }
}

void MainWindow::drawPiece(QPainter& painter,int boardX,int boardY){
    //获取信息
    int centerX = board->boardToWindowX(boardY),centerY = board->boardToWindowY(boardX);
    int val = board->board[boardX][boardY];
    if(val != 0){
        //绘制准备
        QString name = board->getName(boardX,boardY);
        QPoint center(centerX,centerY);
        QLinearGradient borderGrad(center - QPoint(radius, radius), center + QPoint(radius, radius));
        QColor q(150, 70, 50);
        borderGrad.setColorAt(0, q);
        borderGrad.setColorAt(0.5, q);
        borderGrad.setColorAt(1, QColor(120, 30, 50));  // 阴影
        // 绘制
        painter.setPen(QPen(Qt::black, 2));
        painter.setBrush(borderGrad);
        painter.drawEllipse(center,radius,radius);

        QFont font("楷体",30,QFont::Bold);
        painter.setFont(font);
        QColor color = val >0?Qt::red:Qt::black;
        painter.setPen(QPen(color, 2));
        painter.drawText(center-QPoint(21,-14),name);
        update();
    }
}
void MainWindow::erasePiece(QPainter& painter,int boardX,int boardY)    //    擦除指定区域的棋子
{
    int centerX = board->boardToWindowX(boardY),centerY = board->boardToWindowY(boardX);
    QRect rect(centerX-radius-1,centerY-radius-1,radius*2+2, radius*2+2);
    painter.setCompositionMode(QPainter::CompositionMode_Clear);
    painter.eraseRect(rect);
    update();
}

bool MainWindow::windowToBoard(int winX, int winY, int& boardX, int& boardY)
{
    // 计算最近的网格点
    int colIdx = qRound((winX - StartPosX) / (double)meshSize) + 1;
    int rowIdx = qRound((winY - StartPosY) / (double)meshSize) + 1;

    // 检查是否在有效范围内
    if (colIdx < 1 || colIdx > 9 || rowIdx < 1 || rowIdx > 10) {
        return false;
    }

    // 检查点击位置是否靠近网格点（允许一定误差）
    int gridX = StartPosX + (colIdx - 1) * meshSize;
    int gridY = StartPosY + (rowIdx - 1) * meshSize;
    int dist = (winX - gridX) * (winX - gridX) + (winY - gridY) * (winY - gridY);

    if (dist > radius * radius) {  // 点击太远，不算有效
        return false;
    }

    boardX = rowIdx;  // 注意：boardX对应行（1-10）
    boardY = colIdx;  // boardY对应列（1-9）
    return true;
}

void MainWindow::mousePressEvent(QMouseEvent* event)
{
    int boardX, boardY;
    if (windowToBoard(event->pos().x(), event->pos().y(), boardX, boardY)) {
        qDebug() << "鼠标点击棋盘:" << boardX << boardY
                 << "棋子:" <<board->getName(boardX,boardY);
        emit boardClicked(boardX, boardY);  // 发送信号
    } else {
        qDebug() << "点击无效区域";
    }
    event->accept();
}
void MainWindow::markPiece(QPainter& painter,int x,int y){
    painter.setPen(QPen(Qt::blue,2,Qt::SolidLine,Qt::SquareCap,Qt::RoundJoin));
    int windowX = board->boardToWindowX(y),windowY = board->boardToWindowY(x);
    painter.drawEllipse(QPoint(windowX,windowY),radius - 1,radius - 1);
    update();
}
void MainWindow::eraseMark(QPainter& painter,int x,int y){
    painter.setPen(QPen(Qt::black,2,Qt::SolidLine,Qt::SquareCap,Qt::RoundJoin));
    int windowX = board->boardToWindowX(y),windowY = board->boardToWindowY(x);
    painter.drawEllipse(QPoint(windowX,windowY),radius - 1,radius - 1);
    update();
}
MainWindow::~MainWindow()
{
    for(int i = 0;i <= row;i++)
    {
        delete board->board[i];
    }
    delete board;
    delete ui;
}
