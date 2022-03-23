#include "boarditem.h"

unsigned int BoardItem::sizeRect = 100;

BoardItem::BoardItem(const QPoint position, const ChessPieceColor chessPieceColor, std::shared_ptr<Chessman> chessman, QWidget *parent)
    : QWidget{parent}
{
    this->position_ = position;
    this->ItemColor_ = chessPieceColor;

    if(chessman != nullptr)
        this->chessman_ = chessman;

    this->setMinimumSize(sizeRect, sizeRect);
}

QPoint BoardItem::getPosition() const
{
    return this->position_;
}

ChessPieceColor BoardItem::getItemColor() const
{
    return this->ItemColor_;
}

std::shared_ptr<Chessman> BoardItem::getChessman()
{
    return this->chessman_;
}

void BoardItem::setChessman(std::shared_ptr<Chessman> chessman)
{
    this->chessman_ = chessman;
}

void BoardItem::selectedItem(bool state)
{
    this->selectedItem_ = state;
    this->update();
}

void BoardItem::possibleCellMove(bool state)
{
    this->possibleCellMove_ = state;
}

void BoardItem::paintItem()
{

}

void BoardItem::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(Qt::PenStyle::NoPen);

    this->ifSelectedItem(painter);

    painter.drawRect(0,0,sizeRect,sizeRect);

    this->ifPossibleCellMove(painter);

    if(this->chessman_ != nullptr)
        painter.drawPixmap(0, 0, this->width(), this->height(), this->chessman_->getPixmap()->scaled(this->width(), this->height()));
}

void BoardItem::mousePressEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    emit this->pressItem(this->getPosition());
}

void BoardItem::ifSelectedItem(QPainter &painter)
{
    if(this->selectedItem_ == true)
    {
        painter.setBrush(QBrush("#BCADA4"));
    }
    else
    {
        if(this->ItemColor_ == ChessPieceColor::black)
            painter.setBrush(QBrush("#8D7970"));/*8D7970*/
        else
            painter.setBrush(QBrush("#EBE0D7"));/*D6C6B9*/
    }
}


void BoardItem::ifPossibleCellMove(QPainter &painter)
{
    painter.setBrush(QBrush("#BCADA4"));
    if(this->possibleCellMove_ == true)
    {
        if(this->getChessman() != nullptr)
        { 
            painter.drawEllipse(5, 5, 90, 90);
            painter.drawEllipse(15, 15, 70, 70);
        }
        else
        {
            painter.drawEllipse(35, 35, 30, 30);
        }
    }
}
