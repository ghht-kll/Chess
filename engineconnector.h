#ifndef ENGINECONNECTOR_H
#define ENGINECONNECTOR_H

#include <QObject>
#include <QList>
#include <QProcess>
#include <QFile>

#include <memory>

#include <move.h>

class EngineConnector : public QObject
{
    Q_OBJECT
public:
    explicit EngineConnector(QObject *parent = nullptr);

    QPair<std::shared_ptr<QPoint>, std::shared_ptr<QPoint>> getNextMove(QList<QString> &list);

private:
    std::shared_ptr<QProcess> process_;
};

#endif // ENGINECONNECTOR_H
