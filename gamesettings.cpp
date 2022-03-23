#include "gamesettings.h"

GameSettings::GameSettings(QWidget *parent)
    : QWidget{parent}
{
    this->vBoxLayoutSetting_ = std::make_shared<QVBoxLayout>();
    this->setLayout(this->vBoxLayoutSetting_.get());

    this->initPushButtons();
}

void GameSettings::newGameSelected()
{
    this->pushButtonNewSimpleGame_->show();
    this->pushButtonNewGameWithAComputer_->show();
    this->update();
}

void GameSettings::singlePlayerSelected()
{
    this->kindofGame_ = KindOfGame::byMyself;
    this->pushButtonChoiceOfBlack_->show();
    this->pushButtonChoiceOfRandom_->show();
    this->pushButtonChoiceOfwhite_->show();
    this->update();
}

void GameSettings::computerGameSelected()
{
    this->kindofGame_ = KindOfGame::withAComputer;
    this->pushButtonChoiceOfBlack_->show();
    this->pushButtonChoiceOfRandom_->show();
    this->pushButtonChoiceOfwhite_->show();
    this->update();
}

void GameSettings::playForBlackSelected()
{
    this->chessPieceColor_ = ChessPieceColor::black;
    this->pushButtonCreateGame_->show();
    this->update();
}

void GameSettings::playForWhiteSelected()
{
    this->chessPieceColor_ = ChessPieceColor::white;
    this->pushButtonCreateGame_->show();
    this->update();
}

void GameSettings::playForRandomSelectes()
{
    qsizetype rand = std::rand() % 1 + 0;

    if(rand == 0)
        this->chessPieceColor_ = ChessPieceColor::black;
    else
        this->chessPieceColor_ = ChessPieceColor::white;

    this->pushButtonCreateGame_->show();
    this->update();
}

void GameSettings::createGameSelected()
{
    this->pushButtonNewSimpleGame_->hide();
    this->pushButtonNewGameWithAComputer_->hide();
    this->pushButtonChoiceOfBlack_->hide();
    this->pushButtonChoiceOfRandom_->hide();
    this->pushButtonChoiceOfwhite_->hide();
    this->pushButtonCreateGame_->hide();
    this->update();

    emit this->newGameCreated();
}

void GameSettings::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(Qt::PenStyle::NoPen);

    painter.setBrush(QBrush("#272522"));
    painter.drawRoundedRect(0, 0, this->width(), this->height(),10,10);
}

void GameSettings::initPushButtons()
{
    this->pushButtonNewGame_ = std::make_shared<QPushButton>("New Game");

    this->pushButtonNewSimpleGame_ = std::make_shared<QPushButton>("New game by myself");
    this->pushButtonNewGameWithAComputer_ = std::make_shared<QPushButton>("New game with a computer");

    this->pushButtonChoiceOfBlack_ = std::make_shared<QPushButton>();
    this->pushButtonChoiceOfBlack_->setIcon(QIcon(":/resource/images/bq.png"));
    this->pushButtonChoiceOfBlack_->setStyleSheet(style);
    this->pushButtonChoiceOfBlack_->setIconSize(QSize(50 ,50));

    this->pushButtonChoiceOfRandom_ = std::make_shared<QPushButton>();
    this->pushButtonChoiceOfRandom_->setIcon(QIcon(":/resource/images/bwq.png"));
    this->pushButtonChoiceOfRandom_->setStyleSheet(style);
    this->pushButtonChoiceOfRandom_->setIconSize(QSize(50 ,50));

    this->pushButtonChoiceOfwhite_ = std::make_shared<QPushButton>();
    this->pushButtonChoiceOfwhite_->setIcon(QIcon(":/resource/images/wq.png"));
    this->pushButtonChoiceOfwhite_->setStyleSheet(style);
    this->pushButtonChoiceOfwhite_->setIconSize(QSize(50 ,50));

    this->hBoxLayoutSetting_ = std::make_shared<QHBoxLayout>(this);
    this->hBoxLayoutSetting_->addWidget(this->pushButtonChoiceOfBlack_.get());
    this->hBoxLayoutSetting_->addWidget(this->pushButtonChoiceOfRandom_.get());
    this->hBoxLayoutSetting_->addWidget(this->pushButtonChoiceOfwhite_.get());

    this->pushButtonCreateGame_ = std::make_shared<QPushButton>("Create");

    this->pushButtonNewGame_->setMinimumWidth(250);
    this->pushButtonNewSimpleGame_->setMinimumWidth(250);
    this->pushButtonNewGameWithAComputer_->setMinimumWidth(250);
    this->pushButtonCreateGame_->setMinimumWidth(250);

    this->pushButtonNewGame_->setStyleSheet(style);
    this->pushButtonNewSimpleGame_->setStyleSheet(style);
    this->pushButtonNewGameWithAComputer_->setStyleSheet(style);
    this->pushButtonCreateGame_->setStyleSheet(style);

    this->vBoxLayoutSetting_->addWidget(this->pushButtonNewGame_.get());
    this->vBoxLayoutSetting_->addWidget(this->pushButtonNewSimpleGame_.get());
    this->vBoxLayoutSetting_->addWidget(this->pushButtonNewGameWithAComputer_.get());
    this->vBoxLayoutSetting_->addLayout(this->hBoxLayoutSetting_.get());
    this->vBoxLayoutSetting_->addWidget(this->pushButtonCreateGame_.get());

    this->pushButtonNewSimpleGame_->hide();
    this->pushButtonNewGameWithAComputer_->hide();
    this->pushButtonChoiceOfBlack_->hide();
    this->pushButtonChoiceOfRandom_->hide();
    this->pushButtonChoiceOfwhite_->hide();
    this->pushButtonCreateGame_->hide();
    this->update();

    this->vBoxLayoutSetting_->setAlignment(Qt::AlignCenter | Qt::AlignTop);

    connect(this->pushButtonNewGame_.get(), &QPushButton::clicked, this, &GameSettings::newGameSelected);

    connect(this->pushButtonNewSimpleGame_.get(), &QPushButton::clicked, this, &GameSettings::singlePlayerSelected);
    connect(this->pushButtonNewGameWithAComputer_.get(), &QPushButton::clicked, this, &GameSettings::computerGameSelected);

    connect(this->pushButtonChoiceOfBlack_.get(), &QPushButton::clicked, this, &GameSettings::playForBlackSelected);
    connect(this->pushButtonChoiceOfRandom_.get(), &QPushButton::clicked, this, &GameSettings::playForRandomSelectes);
    connect(this->pushButtonChoiceOfwhite_.get(), &QPushButton::clicked, this, &GameSettings::playForWhiteSelected);

    connect(this->pushButtonCreateGame_.get(), &QPushButton::clicked, this, &GameSettings::createGameSelected);

}


