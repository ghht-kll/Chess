#include "move.h"

QString Move::getToUci(QPoint &from, QPoint &to)
{
    return map[from.y() + 1] + QString::number(std::abs(8 - from.x()))
            + map[to.y() + 1] + QString::number(std::abs(8 - to.x()));
}

QPair<std::shared_ptr<QPoint>, std::shared_ptr<QPoint>> Move::getToPoints(QString &str)
{
    QString c0 = str[1];
    QString c1 = str[3];

    qsizetype y0 = map.key(str[0]) - 1;
    qsizetype x0 = std::abs(8 - c0.toInt());

    qsizetype y1 = map.key(str[2]) - 1;
    qsizetype x1 = std::abs(8 - c1.toInt());

    return qMakePair(std::make_shared<QPoint>(x0, y0), std::make_shared<QPoint>(x1, y1));
}
