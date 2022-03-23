#include "logic.h"

Logic::Logic(QVector<QVector<std::shared_ptr<BoardItem>>> *boardItems, ChessPieceColor &chessPieceColor, QObject *parent)
    : QObject{parent}
{
    this->boardItems_ = boardItems;
    this->chessPieceColor_ = chessPieceColor;
}

void Logic::setNewGame(ChessPieceColor chessPieceColor, KindOfGame kindOfGame)
{
    this->chessPieceColor_ = chessPieceColor;
    this->kindOfGame_ = kindOfGame;
    this->movesHistory_.clear();
}

void Logic::pressItems(QPoint point)
{
    if(this->cellSelected == false and this->isEmptyItem(point))
    {
        this->point_ = point;
        this->cellSelected = true;
        this->boardItems_->at(point.x()).at(point.y()).get()->selectedItem(true);
        this->validatePawn();
    }
    else if(this->cellSelected == true and this->point_ != point)
    {
        if(this->possibleMoves_.indexOf(point) != -1)
        {
            this->moveChessPiece(this->point_, point);
            if(this->kindOfGame_ == KindOfGame::withAComputer)
            {
                this->getComputerMove();
            }
            else if(this->kindOfGame_ == KindOfGame::byMyself)
            {
                this->transform();
                this->changeSides();
            }
        }
        this->boardItems_->at(point_.x()).at(point_.y()).get()->selectedItem(false);
        this->cellSelected = false;
        clearPossibleMoves();
    }
    else if(this->cellSelected == true and this->point_ == point)
    {
        this->boardItems_->at(point_.x()).at(point_.y()).get()->selectedItem(false);
        this->cellSelected = false;
        clearPossibleMoves();
    }
}

void Logic::validatePawn()
{
    QString color;
    if(this->chessPieceColor_ == ChessPieceColor::white)
        color = "w";
    else color = "b";
    if(this->boardItems_->at(point_.x()).at(point_.y()).get()->getChessman()->getName() == color + "p")
        possiblePawnMoves();

    if(this->boardItems_->at(point_.x()).at(point_.y()).get()->getChessman()->getName() == color + "b")
        possibleBishopMoves();

    if(this->boardItems_->at(point_.x()).at(point_.y()).get()->getChessman()->getName() == color + "n")
        possibleKnightMoves();

    if(this->boardItems_->at(point_.x()).at(point_.y()).get()->getChessman()->getName() == color + "r")
        possibleRookMoves();

    if(this->boardItems_->at(point_.x()).at(point_.y()).get()->getChessman()->getName() == color + "q")
        possibleQueenMoves();

    if(this->boardItems_->at(point_.x()).at(point_.y()).get()->getChessman()->getName() == color + "k")
        possibleKingMoves();

    for(auto &i : this->possibleMoves_)
    {
        this->boardItems_->at(i.x()).at(i.y()).get()->possibleCellMove(true);
        this->boardItems_->at(i.x()).at(i.y()).get()->update();
    }
}

void Logic::possiblePawnMoves()
{
    if(not this->isEmptyItem(QPoint(this->point_.x() - 1, this->point_.y())) and point_.x() - 1 >= 0)
    {
        this->possibleMoves_.push_back(QPoint(point_.x() - 1, point_.y()));

        if(not this->isEmptyItem(QPoint(this->point_.x() - 2, this->point_.y())) and this->point_.x() == 6)
        {
            this->possibleMoves_.push_back(QPoint(point_.x() - 2, point_.y()));
        }
    }
    if(this->isEmptyItem(QPoint(this->point_.x() - 1, this->point_.y() - 1)) and point_.x() - 1 >= 0 and point_.y() >= 0)
    {
        if(this->boardItems_->at(this->point_.x() - 1).at( this->point_.y() - 1).get()->getChessman()->getChessPieceColor()
                != this->boardItems_->at(this->point_.x()).at( this->point_.y()).get()->getChessman()->getChessPieceColor())
        {
            this->possibleMoves_.push_back(QPoint(point_.x() - 1, point_.y() - 1));
        }
    }
    if(this->isEmptyItem(QPoint(this->point_.x() - 1, this->point_.y() + 1)) and point_.x() - 1 >= 0 and point_.y() <= 7)
    {
        if(this->boardItems_->at(this->point_.x() - 1).at( this->point_.y() + 1).get()->getChessman()->getChessPieceColor()
                != this->boardItems_->at(this->point_.x()).at( this->point_.y()).get()->getChessman()->getChessPieceColor())
        {
            this->possibleMoves_.push_back(QPoint(point_.x() - 1, point_.y() + 1));
        }
    }
}

void Logic::possibleBishopMoves()
{
    this->helperFunction(QPoint(this->point_), -1, -1, [&](QPoint& point)
    {
        return point.x() - 1 >= 0 and point.y() - 1 >= 0;
    });

    this->helperFunction(QPoint(this->point_), 1, 1, [&](QPoint& point)
    {
        return point.x() + 1 <= 7 and point.y() + 1 <= 7;
    });

    this->helperFunction(QPoint(this->point_), -1, 1, [&](QPoint& point)
    {
        return point.x() - 1 >= 0 and point.y() + 1 <= 7;
    });

    this->helperFunction(QPoint(this->point_), 1, -1, [&](QPoint& point)
    {
        return point.x() + 1 <= 7 and point.y() - 1 >= 0;
    });
}

void Logic::possibleKnightMoves()
{
    this->helperFunction(QPoint(this->point_.x() - 2, this->point_.y() + 1),[&](void)
    {
        return point_.x() - 2 >= 0 and point_.y() + 1 <= 7;
    });

    this->helperFunction(QPoint(this->point_.x() - 2, this->point_.y() - 1),[&](void)
    {
        return point_.x() - 2 >= 0 and point_.y() - 1 >= 0;
    });

    this->helperFunction(QPoint(this->point_.x() - 1, this->point_.y() - 2),[&](void)
    {
        return point_.x() - 1 >= 0 and point_.y() - 2 >= 0;
    });

    this->helperFunction(QPoint(this->point_.x() - 1, this->point_.y() + 2),[&](void)
    {
        return point_.x() - 1 >= 0 and point_.y() + 2 <= 7;
    });

    this->helperFunction(QPoint(this->point_.x() + 2, this->point_.y() - 1),[&](void)
    {
        return point_.x() + 2 <= 7 and point_.y() - 1 >= 0;
    });

    this->helperFunction(QPoint(this->point_.x() + 1, this->point_.y() - 2),[&](void)
    {
        return point_.x() + 1 <= 7 and point_.y() - 2 >= 0;
    });

    this->helperFunction(QPoint(this->point_.x() + 1, this->point_.y() + 2),[&](void)
    {
        return point_.x() + 1 <= 7 and point_.y() + 2 <= 7;
    });

    this->helperFunction(QPoint(this->point_.x() + 2, this->point_.y() + 1),[&](void)
    {
        return point_.x() + 2 <= 7 and point_.y() + 1 <= 7;
    });
}

void Logic::possibleRookMoves()
{

    this->helperFunction(QPoint(this->point_), -1, 0, [&](QPoint& point)
    {
        return point.x() - 1 >= 0;
    });

    this->helperFunction(QPoint(this->point_), 1, 0, [&](QPoint& point)
    {
        return point.x() + 1 <= 7;
    });

    this->helperFunction(QPoint(this->point_), 0, 1, [&](QPoint& point)
    {
        return point.y() + 1 <= 7;
    });

    this->helperFunction(QPoint(this->point_), 0, -1, [&](QPoint& point)
    {
        return point.y() - 1 >= 0;
    });
}

void Logic::possibleQueenMoves()
{
    possibleRookMoves();
    possibleBishopMoves();
}

void Logic::possibleKingMoves()
{      
    this->helperFunction(QPoint(this->point_.x() + 1, this->point_.y() + 1),[&](void)
    {
        return point_.x() + 1 <= 7 and point_.y() + 1 <= 7;
    });

    this->helperFunction(QPoint(this->point_.x() - 1, this->point_.y() + 1),[&](void)
    {
        return point_.x() - 1 >= 0 and point_.y() + 1 <= 7;
    });

    this->helperFunction(QPoint(this->point_.x() + 1, this->point_.y() - 1),[&](void)
    {
        return point_.x() + 1 <= 7 and point_.y() - 1 >= 0;
    });

    this->helperFunction(QPoint(this->point_.x() - 1, this->point_.y() - 1),[&](void)
    {
        return point_.x() - 1 and point_.y() - 1 >= 0;
    });

    this->helperFunction(QPoint(this->point_.x() - 1, this->point_.y()),[&](void)
    {
        return point_.x() - 1 >= 0;
    });

    this->helperFunction(QPoint(this->point_.x() + 1, this->point_.y()),[&](void)
    {
        return point_.x() + 1 <= 7;
    });

    this->helperFunction(QPoint(this->point_.x(), this->point_.y() - 1),[&](void)
    {
        return point_.y() - 1 >= 0;
    });

    this->helperFunction(QPoint(this->point_.x(), this->point_.y() + 1),[&](void)
    {
        return point_.y() + 1 <= 7;
    });
}

void Logic::getComputerMove()
{
    EngineConnector engineConnector;
    QPair<std::shared_ptr<QPoint>, std::shared_ptr<QPoint>> pair = engineConnector.getNextMove(this->movesHistory_);
    this->moveChessPiece(*pair.first.get(), *pair.second.get());
}

void Logic::helperFunction(const QPoint point, const std::function<bool ()> &fn)
{
    if(fn())
    {
        if(this->isEmptyItem(point))
        {
            if(this->isAnotherColor(point))
                this->possibleMoves_.push_back(point);
        }
        else
        {
            this->possibleMoves_.push_back(point);
        }
    }
}

void Logic::helperFunction(QPoint point, const qsizetype dx, const qsizetype dy, const std::function<bool(QPoint&)> &fn)
{
    while(fn(point))
    {
        point.setX(point.x() + dx);  point.setY(point.y() + dy);

        if(this->isEmptyItem(point) == true)
        {
            if(this->boardItems_->at(point.x()).at(point.y()).get()->getChessman()->getChessPieceColor()
                    != this->boardItems_->at(this->point_.x()).at(this->point_.y()).get()->getChessman()->getChessPieceColor())
                this->possibleMoves_.push_back(point);
            break;
        }
        else
        {
            this->possibleMoves_.push_back(point);
        }
    }
}

bool Logic::isEmptyItem(QPoint point)
{
    if(point.x() >= 0 and point.y() <= 7 and point.y() >= 0 and point.y() <= 7)
    {
        if(this->boardItems_->at(point.x()).at(point.y()).get()->getChessman() != nullptr)
            return true;
        else return false;
    }
    else return false;
}

bool Logic::isAnotherColor(QPoint point)
{
    if(this->boardItems_->at(point.x()).at(point.y()).get()->getChessman()->getChessPieceColor()
        != this->boardItems_->at(this->point_.x()).at(this->point_.y()).get()->getChessman()->getChessPieceColor())
        return true;
    else return false;
}

void Logic::moveChessPiece(QPoint from, QPoint to)
{
    qDebug() << "from: " << from << " to: " << to;
    qDebug() << "to Uci: " << Move::getToUci(from, to);

    this->lastCompletedMove_ = QPair<QPoint&, QPoint&>(from, to);

    this->movesHistory_.push_back(Move::getToUci(from, to));
    auto item = this->boardItems_->at(from.x()).at(from.y()).get()->getChessman();
    this->boardItems_->at(from.x()).at(from.y()).get()->setChessman(nullptr);

    this->boardItems_->at(to.x()).at(to.y()).get()->setChessman(item);

    this->boardItems_->at(from.x()).at(from.y()).get()->update();
    this->boardItems_->at(to.x()).at(to.y()).get()->update();
}

void Logic::markTheLastMove(QPoint &from, QPoint &to)
{
    this->boardItems_->at(this->lastCompletedMove_.first.x()).at(this->lastCompletedMove_.first.y())->selectedItem(false);
    this->boardItems_->at(this->lastCompletedMove_.second.x()).at(this->lastCompletedMove_.second.y())->selectedItem(false);

    this->lastCompletedMove_ = QPair<QPoint&, QPoint&>(from, to);

    this->boardItems_->at(this->lastCompletedMove_.first.x()).at(this->lastCompletedMove_.first.y())->selectedItem(true);
    this->boardItems_->at(this->lastCompletedMove_.second.x()).at(this->lastCompletedMove_.second.y())->selectedItem(true);
}

void Logic::clearPossibleMoves()
{
    for(auto &i : this->possibleMoves_)
    {
        this->boardItems_->at(i.x()).at(i.y()).get()->possibleCellMove(false);
        this->boardItems_->at(i.x()).at(i.y()).get()->update();
    }
    this->possibleMoves_.clear();   
}

void Logic::transform()
{
    int i{0}, x{0}, j{0};

    for(i = 0, x = this->boardItems_->size() - 1; i < this->boardItems_->size() / 2; i++, x--)
    {
        for(j = 0; j < this->boardItems_->size(); j++)
        {
            auto s0 = this->boardItems_->at(i).at(j)->getChessman();
            auto s1 = this->boardItems_->at(x).at(j)->getChessman();
            this->boardItems_->at(i).at(j)->setChessman(nullptr);
            this->boardItems_->at(x).at(j)->setChessman(nullptr);
            this->boardItems_->at(i).at(j)->setChessman(s1);
            this->boardItems_->at(x).at(j)->setChessman(s0);
        }
    }
}

void Logic::changeSides()
{
    if(this->chessPieceColor_ == ChessPieceColor::white)
        this->chessPieceColor_ = ChessPieceColor::black;
    else this->chessPieceColor_ = ChessPieceColor::white;
}

