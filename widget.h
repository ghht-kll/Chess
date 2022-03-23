#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QDebug>
#include <QPushButton>
#include <QVBoxLayout>

#include <memory>

#include "chessboard.h"
#include "kindOfGame.h"
#include "gamesettings.h"
#include "logic.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void createNewGameByMyself();
    void createNewGameWithAComputer();
    void createNewGame();

private:
    void resizeEvent(QResizeEvent *event) override;
    void initSettingLayout();

private:
    Ui::Widget *ui;
    std::shared_ptr<ChessBoard> chessBoard_;
    std::shared_ptr<QGridLayout> gridLayout_;
    std::shared_ptr<Logic> logic_;

    std::shared_ptr<GameSettings> gameSettings_;

    KindOfGame kindofGame_;
    ChessPieceColor chessPieceColor_;
};
#endif // WIDGET_H
