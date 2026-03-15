#ifndef CHESSPIECE_H
#define CHESSPIECE_H

#include <QObject>

class ChessPiece : public QObject
{
    Q_OBJECT
public:
    explicit ChessPiece(QObject *parent = nullptr);

    ChessPiece(){};


signals:
};

#endif // CHESSPIECE_H
