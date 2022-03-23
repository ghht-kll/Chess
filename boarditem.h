#ifndef BOARDITEM_H
#define BOARDITEM_H

#include <QWidget>
#include <QString>
#include <QPainter>
#include <QPixmap>
#include <QDebug>
#include <QRect>
#include <QPainterPath>
#include <memory>
#include "chessman.h"

class BoardItem : public QWidget
{
    Q_OBJECT
public:
    explicit BoardItem(const QPoint position, const ChessPieceColor ItemColor_,
                       std::shared_ptr<Chessman> chessman = nullptr, QWidget *parent = nullptr);

    QPoint getPosition() const;
    ChessPieceColor getItemColor() const;
    std::shared_ptr<Chessman> getChessman();

    void setChessman(std::shared_ptr<Chessman> chessman);
    void selectedItem(bool state);
    void possibleCellMove(bool state);

    void paintItem();

    static unsigned int sizeRect;

signals:
    void pressItem(const QPoint point);

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

    void ifSelectedItem(QPainter &painter);
    void ifPossibleCellMove(QPainter &painter);
private:
    bool selectedItem_ = false;
    bool possibleCellMove_ = false;
    QPoint position_;
    ChessPieceColor ItemColor_;
    std::shared_ptr<Chessman> chessman_;
};

#endif // BOARDITEM_H
