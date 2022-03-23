#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <QGridLayout>
#include <QObject>
#include <QWidget>
#include <memory>
#include <QVector>
#include "boarditem.h"
//#include "logic.h"

class ChessBoard : public QWidget
{
    Q_OBJECT
public:
    ChessBoard(QWidget *parent = nullptr);

    void initChessPieces(ChessPieceColor &chessPieceColor);
    void clearBoard();
    QVector<QVector<std::shared_ptr<BoardItem>>> *getBoardItems();

protected:
    void resizeEvent(QResizeEvent *event) override;

    void initBoardSize();
    void initBordItemColor();
    void initGridLayout();

private:
    QVector<QVector<std::shared_ptr<BoardItem>>> boardItems_;
    std::shared_ptr<QGridLayout> gridLayout_;
    //std::shared_ptr<Logic> logic_;

    const qsizetype numberOfElements_ = 8;
};

#endif // CHESSBOARD_H
