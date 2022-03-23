#include "chessman.h"

Chessman::Chessman(QString path, QObject *parrent)
    :QObject{parrent}
{
    this->name_ = QString(path[18]) + QString(path[19]);

    if(path[18] == 'w')
        this->ItemColor_ = ChessPieceColor::white;
    else
        this->ItemColor_ = ChessPieceColor::black;

    this->pixmap_ = std::make_shared<QPixmap>(path);
    this->path_ = path;
}

QString Chessman::getName() const
{
    return this->name_;
}

ChessPieceColor Chessman::getChessPieceColor() const
{
    return this->ItemColor_;
}

std::shared_ptr<QPixmap> Chessman::getPixmap() const
{
    return this->pixmap_;
}
