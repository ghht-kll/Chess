#include "widget.h"
#include "ui_widget.h"
#include "gamesettings.h"

#include <QLabel>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->chessBoard_ = std::make_shared<ChessBoard>(this);
    this->gridLayout_ = std::make_shared<QGridLayout>(this);
    this->setLayout(this->gridLayout_.get());

    this->setStyleSheet("background-color: #2E2F30;");

    this->gridLayout_->addWidget(this->chessBoard_.get());
    this->setLayout(this->gridLayout_.get());

    this->initSettingLayout();

    this->chessPieceColor_ = ChessPieceColor::black;
    this->logic_ = std::make_shared<Logic>(this->chessBoard_->getBoardItems(), this->chessPieceColor_);

    for(auto &i : *this->chessBoard_->getBoardItems())
    {
        for(auto &j : i)
        {
            connect(j.get(), SIGNAL(pressItem(QPoint)), this->logic_.get(), SLOT(pressItems(QPoint)));
            connect(j.get(), SIGNAL(pressItem(QPoint)), this, SLOT(update()));
        }
    }
}

void Widget::createNewGameByMyself()
{
    this->chessBoard_->initChessPieces(this->chessPieceColor_);
    this->logic_->setNewGame(this->chessPieceColor_, KindOfGame::byMyself);
    this->chessBoard_->update();
}

void Widget::createNewGameWithAComputer()
{
    this->chessBoard_->initChessPieces(this->chessPieceColor_);
    this->logic_->setNewGame(this->chessPieceColor_, KindOfGame::withAComputer);
    this->chessBoard_->update();
}

void Widget::createNewGame()
{
    this->chessPieceColor_ = this->gameSettings_->chessPieceColor_;
    this->kindofGame_ = this->gameSettings_->kindofGame_;

    this->chessBoard_->initChessPieces(this->chessPieceColor_);
    this->logic_->setNewGame(this->chessPieceColor_, this->kindofGame_);
    this->chessBoard_->update();
}

void Widget::resizeEvent(QResizeEvent *event)
{
    BoardItem::sizeRect = this->width() / 8;
}

void Widget::initSettingLayout()
{   
    this->gameSettings_ = std::make_shared<GameSettings>(this);
    this->gridLayout_->addWidget(this->gameSettings_.get(), 0, 1);

    //connect(this->gameSettings_->pushButtonNewSimpleGame_.get(), &QPushButton::clicked, this, &Widget::createNewGameByMyself);
    //connect(this->gameSettings_->pushButtonNewGameWithAComputer_.get(), &QPushButton::clicked, this, &Widget::createNewGameWithAComputer);
    connect(this->gameSettings_.get(), &GameSettings::newGameCreated, this, &Widget::createNewGame);
}

Widget::~Widget()
{
    delete ui;
}


