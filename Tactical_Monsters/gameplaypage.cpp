#include "gameplaypage.h"
#include "ui_gameplaypage.h"

GamePlayPage::GamePlayPage(const QString& player1, const QString& player2, QWidget *parent)
    : QWidget(parent), ui(new Ui::GamePlayPage)
{
    ui->setupUi(this);

    this->setFixedSize(1350, 700);
    this->setWindowTitle("Tactical Monsters - Gameplay");

    // Set player names
    ui->labelPlayer1->setText("Player 1: " + player1);
    ui->labelPlayer2->setText("Player 2: " + player2);
}

GamePlayPage::~GamePlayPage()
{
    delete ui;
}
