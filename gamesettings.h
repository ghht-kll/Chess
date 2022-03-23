#ifndef GAMESETTINGS_H
#define GAMESETTINGS_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QPainter>
#include <QPainterPath>
#include <QString>
#include <QTime>

#include <memory>
#include <iostream>

#include "kindOfGame.h"
#include "ChessPieceColor.h"


class GameSettings : public QWidget
{
    Q_OBJECT
public:
    explicit GameSettings(QWidget *parent = nullptr);

    std::shared_ptr<QGridLayout> gridLayout_;
    std::shared_ptr<QVBoxLayout> vBoxLayoutSetting_;
    std::shared_ptr<QHBoxLayout> hBoxLayoutSetting_;
    std::shared_ptr<QPushButton> pushButtonNewGame_;
    std::shared_ptr<QPushButton> pushButtonNewSimpleGame_;
    std::shared_ptr<QPushButton> pushButtonNewGameWithAComputer_;
    std::shared_ptr<QPushButton> pushButtonChoiceOfBlack_;
    std::shared_ptr<QPushButton> pushButtonChoiceOfwhite_;
    std::shared_ptr<QPushButton> pushButtonChoiceOfRandom_;

    std::shared_ptr<QPushButton> pushButtonCreateGame_;

    KindOfGame kindofGame_;
    ChessPieceColor chessPieceColor_;

protected slots:
    void newGameSelected();

    void singlePlayerSelected();
    void computerGameSelected();

    void playForBlackSelected();
    void playForWhiteSelected();
    void playForRandomSelectes();

    void createGameSelected();

signals:
    void newGameCreated();

protected:
    void paintEvent(QPaintEvent *event) override;

    void initPushButtons();


    QString style =
              "background-color: #32312F;"
              "border-radius: 4px;"
              "color: #FFFFFF;"
              "font-family: Graphik,-apple-system,system-ui,""Segoe UI"",Roboto,Oxygen,Ubuntu,Cantarell,""Fira Sans"",""Droid Sans"",""Helvetica Neue"",sans-serif;"
              "font-size: 14px;"
              "line-height: 1.15;"
              "padding: 12px 16px;"
              "position: relative;"
              "text-align: center;"
              "text-transform: none;"
              "width: fit-content;";
};

#endif // GAMESETTINGS_H



