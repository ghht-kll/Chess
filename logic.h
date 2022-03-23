#ifndef LOGIC_H
#define LOGIC_H

#include <QObject>
#include <QVector>
#include <QDebug>
#include <QList>
#include <QPair>

#include <memory>
#include <algorithm>

#include "boarditem.h"
#include "chessman.h"
#include "move.h"
#include "engineconnector.h"
#include "kindOfGame.h"

class Logic : public QObject
{
    Q_OBJECT
public:
    explicit Logic(QVector<QVector<std::shared_ptr<BoardItem>>> *boardItems, ChessPieceColor &chessPieceColor, QObject *parent = nullptr);

    void setNewGame(ChessPieceColor chessPieceColor, KindOfGame kindOfGame);

public slots:
    void pressItems(QPoint point);

private:
    void validatePawn();
    void possiblePawnMoves();
    void possibleBishopMoves();
    void possibleKnightMoves();
    void possibleRookMoves();
    void possibleQueenMoves();
    void possibleKingMoves();

    void getComputerMove();

    void helperFunction(const QPoint point, const std::function<bool(void)>& fn);
    void helperFunction(QPoint point, const qsizetype dx, const qsizetype dy, const std::function<bool(QPoint&)>& fn);

    bool isEmptyItem(QPoint point);
    bool isAnotherColor(QPoint point);
    void moveChessPiece(QPoint from, QPoint to);
    void markTheLastMove(QPoint &from, QPoint &to);
    void clearPossibleMoves();
    void transform();
    void changeSides();

    QPoint point_;
    bool cellSelected = false;
    ChessPieceColor chessPieceColor_;
    KindOfGame kindOfGame_;
    QVector<QPoint> possibleMoves_;
    QVector<QVector<std::shared_ptr<BoardItem>>> *boardItems_;
    QList<QString> movesHistory_;

    QPair<QPoint&, QPoint&> lastCompletedMove_;
};



#endif // LOGIC_H
