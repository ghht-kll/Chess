#ifndef CHESSMAN_H
#define CHESSMAN_H

#include <QObject>
#include <QPixmap>
#include <memory>
#include "ChessPieceColor.h"

class Chessman : QObject
{
    Q_OBJECT
public:
    Chessman(QString path, QObject *parrent = nullptr);

    QString getName() const;
    ChessPieceColor getChessPieceColor() const;
    std::shared_ptr<QPixmap> getPixmap() const;

private:
    QString path_;
    QString name_;
    ChessPieceColor ItemColor_;
    std::shared_ptr<QPixmap> pixmap_;
};

#endif // CHESSMAN_H
