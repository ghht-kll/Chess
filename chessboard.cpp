#include "chessboard.h"

ChessBoard::ChessBoard(QWidget *parent)
    : QWidget{parent}
{
    this->initBordItemColor();
    this->initGridLayout();
}

void ChessBoard::initBoardSize()
{
    this->gridLayout_->setSpacing(0);
    //this->setMaximumSize(sizeRect * this->numberOfElements_, sizeRect * this->numberOfElements_);
    //this->setMinimumSize(sizeRect * this->numberOfElements_, sizeRect * this->numberOfElements_);
}

void ChessBoard::initBordItemColor()
{
    for(qsizetype i = 0; i < this->numberOfElements_; i++)
    {
        QVector<std::shared_ptr<BoardItem>> vec;
        for(qsizetype j = 0; j < this->numberOfElements_; j++)
        {
            ChessPieceColor chessPieceColor;

            if(i % 2 == 0)
            {
                if(j % 2 == 0)
                    chessPieceColor = ChessPieceColor::white;
                else
                    chessPieceColor = ChessPieceColor::black;
            }
            else
            {
                if(j % 2 == 0)
                    chessPieceColor = ChessPieceColor::black;
                else
                    chessPieceColor = ChessPieceColor::white;
            }
            auto item = std::make_shared<BoardItem>(QPoint(i, j), chessPieceColor);
            vec.push_back(item);
        }
        this->boardItems_.push_back(vec);
    }
}

void ChessBoard::initGridLayout()
{
    this->gridLayout_ = std::make_shared<QGridLayout>(this);
    this->initBoardSize();

    for(qsizetype i = 0; i < this->numberOfElements_; i++)
    {
        for(qsizetype j = 0; j < this->numberOfElements_; j++)
        {
            this->gridLayout_->addWidget(this->boardItems_[i][j].get(), i, j);
        }
    }
    this->setLayout(this->gridLayout_.get());
}

void ChessBoard::initChessPieces(ChessPieceColor &chessPieceColor)
{
    this->clearBoard();

    int black {0}, white {0};

    if(chessPieceColor == ChessPieceColor::black) { black = 7;  white = 0; }
    else if(chessPieceColor == ChessPieceColor::white) { black = 0;  white = 7; }
    else return;

    this->boardItems_.at(white).at(0)->setChessman(std::make_shared<Chessman>(":/resource/images/wr.png"));
    this->boardItems_.at(white).at(1)->setChessman(std::make_shared<Chessman>(":/resource/images/wn.png"));
    this->boardItems_.at(white).at(2)->setChessman(std::make_shared<Chessman>(":/resource/images/wb.png"));
    this->boardItems_.at(white).at(3)->setChessman(std::make_shared<Chessman>(":/resource/images/wq.png"));
    this->boardItems_.at(white).at(4)->setChessman(std::make_shared<Chessman>(":/resource/images/wk.png"));
    this->boardItems_.at(white).at(5)->setChessman(std::make_shared<Chessman>(":/resource/images/wb.png"));
    this->boardItems_.at(white).at(6)->setChessman(std::make_shared<Chessman>(":/resource/images/wn.png"));
    this->boardItems_.at(white).at(7)->setChessman(std::make_shared<Chessman>(":/resource/images/wr.png"));

    this->boardItems_.at(black).at(0)->setChessman(std::make_shared<Chessman>(":/resource/images/br.png"));
    this->boardItems_.at(black).at(1)->setChessman(std::make_shared<Chessman>(":/resource/images/bn.png"));
    this->boardItems_.at(black).at(2)->setChessman(std::make_shared<Chessman>(":/resource/images/bb.png"));
    this->boardItems_.at(black).at(3)->setChessman(std::make_shared<Chessman>(":/resource/images/bq.png"));
    this->boardItems_.at(black).at(4)->setChessman(std::make_shared<Chessman>(":/resource/images/bk.png"));
    this->boardItems_.at(black).at(5)->setChessman(std::make_shared<Chessman>(":/resource/images/bb.png"));
    this->boardItems_.at(black).at(6)->setChessman(std::make_shared<Chessman>(":/resource/images/bn.png"));
    this->boardItems_.at(black).at(7)->setChessman(std::make_shared<Chessman>(":/resource/images/br.png"));

    for(qsizetype i = 0; i < this->numberOfElements_; i++)
    {
        if(chessPieceColor == ChessPieceColor::black)
        {
            this->boardItems_.at(white + 1).at(i)->setChessman(std::make_shared<Chessman>(":/resource/images/wp.png"));
            this->boardItems_.at(black - 1).at(i)->setChessman(std::make_shared<Chessman>(":/resource/images/bp.png"));
        }
        else
        {
            this->boardItems_.at(white - 1).at(i)->setChessman(std::make_shared<Chessman>(":/resource/images/wp.png"));
            this->boardItems_.at(black + 1).at(i)->setChessman(std::make_shared<Chessman>(":/resource/images/bp.png"));
        }
    }
}

void ChessBoard::clearBoard()
{
    for(auto &i : this->boardItems_)
        for(auto &j : i)
            j->setChessman(nullptr);
}

QVector<QVector<std::shared_ptr<BoardItem>>> *ChessBoard::getBoardItems()
{
    return &this->boardItems_;
}

void ChessBoard::resizeEvent(QResizeEvent *event)
{
    this->setMinimumWidth(this->height());
}
