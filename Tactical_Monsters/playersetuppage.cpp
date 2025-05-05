#include "playersetuppage.h"
#include "gameplaypage.h"

#include <QVBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include <QGraphicsOpacityEffect>
#include <QFont>

PlayerSetupPage::PlayerSetupPage(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("Player Setup");
    resize(400, 300);
    setStyleSheet("background-color: #f5f7fa;");

    auto* layout = new QVBoxLayout(this);
    layout->setContentsMargins(40, 40, 40, 40);
    layout->setSpacing(20);

    QFont labelFont("Segoe UI", 12, QFont::Bold);
    QFont inputFont("Segoe UI", 11);
    QFont buttonFont("Segoe UI", 12, QFont::DemiBold);

    QLabel* label1 = new QLabel("Player 1 Name:", this);
    label1->setFont(labelFont);
    player1Input = new QLineEdit(this);
    player1Input->setFont(inputFont);
    player1Input->setPlaceholderText("Enter name...");
    player1Input->setStyleSheet(
        "QLineEdit { padding: 8px; border-radius: 10px; border: 1px solid #ccc; background: #ffffff; }"
        "QLineEdit:hover { border: 1px solid #6666ff; }"
        );

    QLabel* label2 = new QLabel("Player 2 Name:", this);
    label2->setFont(labelFont);
    player2Input = new QLineEdit(this);
    player2Input->setFont(inputFont);
    player2Input->setPlaceholderText("Enter name...");
    player2Input->setStyleSheet(
        "QLineEdit { padding: 8px; border-radius: 10px; border: 1px solid #ccc; background: #ffffff; }"
        "QLineEdit:hover { border: 1px solid #6666ff; }"
        );

    startButton = new QPushButton("Start Game", this);
    startButton->setFont(buttonFont);
    startButton->setCursor(Qt::PointingHandCursor);
    startButton->setStyleSheet(
        "QPushButton { background-color: #667eea; color: white; padding: 10px; border-radius: 10px; }"
        "QPushButton:hover { background-color: #5a67d8; }"
        "QPushButton:pressed { background-color: #4c51bf; }"
        );

    connect(startButton, &QPushButton::clicked, this, &PlayerSetupPage::startGame);

    layout->addWidget(label1);
    layout->addWidget(player1Input);
    layout->addWidget(label2);
    layout->addWidget(player2Input);
    layout->addWidget(startButton);

    // affects
    QGraphicsOpacityEffect* effect = new QGraphicsOpacityEffect(this);
    setGraphicsEffect(effect);
    fadeInAnimation = new QPropertyAnimation(effect, "opacity", this);
    fadeInAnimation->setDuration(800);
    fadeInAnimation->setStartValue(0.0);
    fadeInAnimation->setEndValue(1.0);
    fadeInAnimation->start();
}

void PlayerSetupPage::startGame()
{
    QString player1 = player1Input->text().trimmed();
    QString player2 = player2Input->text().trimmed();

    if (player1.isEmpty() || player2.isEmpty()) {
        QMessageBox::warning(this, "Missing Info", "Please enter both player names.");
        return;
    }

    auto* gamePage = new GamePlayPage(player1, player2); // Pass player names here if needed

    gamePage->show();
    this->close();
}
