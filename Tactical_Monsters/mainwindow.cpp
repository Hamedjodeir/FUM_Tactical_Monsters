#include "mainwindow.h"
#include "mainmenu.h"
#include <QVBoxLayout>
#include <QSpacerItem>
#include <QGraphicsOpacityEffect>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->resize(800, 500);

    this->setStyleSheet("QMainWindow {"
                        "background-image: url(:/Assets/splash_background.jpg);"
                        "background-repeat: no-repeat;"
                        "background-position: center;"
                        "background-size: cover;"
                        "}");

    QWidget *central = new QWidget(this);
    this->setCentralWidget(central);

    QVBoxLayout *layout = new QVBoxLayout(central);

    layout->addSpacerItem(new QSpacerItem(20, 200, QSizePolicy::Minimum, QSizePolicy::Expanding));

    // Welcome
    welcomeLabel = new QLabel("Welcome to Tactical Monsters", this);
    welcomeLabel->setAlignment(Qt::AlignCenter);
    welcomeLabel->setStyleSheet("QLabel { font-size: 28px; font-weight: bold; color: white; }");
    layout->addWidget(welcomeLabel);

    layout->addSpacerItem(new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding));

    continueButton = new QPushButton("Continue to Main Menu", this);
    continueButton->setFixedSize(250, 50);
    continueButton->setStyleSheet(
        "QPushButton {"
        "font-size: 18px;"
        "background-color: #3498db;"
        "color: white;"
        "border-radius: 10px;"
        "}"
        "QPushButton:hover {"
        "background-color: #2980b9;"
        "}"
        );
    layout->addWidget(continueButton, 0, Qt::AlignHCenter);

    layout->addSpacerItem(new QSpacerItem(20, 100, QSizePolicy::Minimum, QSizePolicy::Expanding));

    connect(continueButton, &QPushButton::clicked, this, &MainWindow::onContinueButtonClicked);

    // animation
    QGraphicsOpacityEffect *labelEffect = new QGraphicsOpacityEffect(this);
    welcomeLabel->setGraphicsEffect(labelEffect);
    welcomeAnimation = new QPropertyAnimation(labelEffect, "opacity", this);
    welcomeAnimation->setDuration(1500);
    welcomeAnimation->setStartValue(0);
    welcomeAnimation->setEndValue(1);
    welcomeAnimation->start();

    QGraphicsOpacityEffect *buttonEffect = new QGraphicsOpacityEffect(this);
    continueButton->setGraphicsEffect(buttonEffect);
    buttonAnimation = new QPropertyAnimation(buttonEffect, "opacity", this);
    buttonAnimation->setDuration(2000);
    buttonAnimation->setStartValue(0);
    buttonAnimation->setEndValue(1);
    buttonAnimation->start();
}

MainWindow::~MainWindow()
{
}

void MainWindow::onContinueButtonClicked()
{
    MainMenu *menu = new MainMenu();
    menu->show();
    this->close();
}
