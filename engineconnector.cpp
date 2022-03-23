#include "engineconnector.h"

EngineConnector::EngineConnector(QObject *parent)
    : QObject{parent}
{   }

QPair<std::shared_ptr<QPoint>, std::shared_ptr<QPoint>> EngineConnector::getNextMove(QList<QString> &list)
{
    QString script = "python scrypt.py ";
    for(const auto &i : list)
        script += i + " ";

    system(script.toUtf8());

    QFile file("lastmove.txt");

    if (!file.open(QIODevice::ReadOnly))
        qWarning("Cannot open file for reading");

    QTextStream in(&file);
    QString result = in.readLine();
    file.close();

    return Move::getToPoints(result);
}
