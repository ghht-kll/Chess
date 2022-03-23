#ifndef MOVE_H
#define MOVE_H

#include <QObject>
#include <QDebug>
#include <QPoint>
#include <QPair>
#include <QMap>

#include <math.h>

static QMap<int, QString> map{
    {1, "a"},   {2, "b"},
    {3, "c"},   {4, "d"},
    {5, "e"},   {6, "f"},
    {7, "g"},   {8, "h"}
};

class Move
{
public:
    static QString getToUci(QPoint &from, QPoint &to);
    static QPair<std::shared_ptr<QPoint>, std::shared_ptr<QPoint>> getToPoints(QString &str);
};

#endif // MOVE_H
