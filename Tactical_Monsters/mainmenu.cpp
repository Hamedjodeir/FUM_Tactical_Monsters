#include "mainmenu.h"
#include "gallerypage.h"
#include "playersetuppage.h"
#include <QVBoxLayout>
#include <QSpacerItem>
#include <QGraphicsOpacityEffect>
#include <QLabel>
#include <QScreen>
#include <QGuiApplication>


MainMenu::MainMenu(QWidget *parent)
    : QMainWindow(parent)
{
    this->resize(1200, 700);
    this->setWindowTitle("Tactical Monsters - Main Menu");

    // Center the window
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect screenGeometry = screen->geometry();
    int x = (screenGeometry.width() - this->width()) / 2;
    int y = 0;
    this->move(x, y);


    this->setStyleSheet("QMainWindow {"
                        "background-image: url(:/Assets/mainmenu_background.png);"
                        "background-repeat: no-repeat;"
                        "background-position: center;"
                        "background-size: cover;"
                        "}");

    QWidget *central = new QWidget(this);
    this->setCentralWidget(central);

    QVBoxLayout *layout = new QVBoxLayout(central);

    layout->addSpacerItem(new QSpacerItem(20, 150, QSizePolicy::Minimum, QSizePolicy::Expanding));

    // Gallery Button
    galleryButton = new QPushButton("Gallery", this);
    galleryButton->setFixedSize(300, 60);
    galleryButton->setStyleSheet(
        "QPushButton {"
        "font-size: 22px;"
        "background-color: #e74c3c;"
        "color: white;"
        "border-radius: 15px;"
        "}"
        "QPushButton:hover {"
        "background-color: #c0392b;"
        "}"
        );
    layout->addWidget(galleryButton, 0, Qt::AlignHCenter);

    layout->addSpacerItem(new QSpacerItem(20, 30, QSizePolicy::Minimum, QSizePolicy::Fixed));

    // Start Game Button
    startGameButton = new QPushButton("Start an Async PVP Game", this);
    startGameButton->setFixedSize(300, 60);
    startGameButton->setStyleSheet(
        "QPushButton {"
        "font-size: 22px;"
        "background-color: #27ae60;"
        "color: white;"
        "border-radius: 15px;"
        "}"
        "QPushButton:hover {"
        "background-color: #1e8449;"
        "}"
        );
    layout->addWidget(startGameButton, 0, Qt::AlignHCenter);

    layout->addSpacerItem(new QSpacerItem(20, 30, QSizePolicy::Minimum, QSizePolicy::Fixed));

    // Help Button
    helpButton = new QPushButton("Help", this);
    helpButton->setFixedSize(150, 40);
    helpButton->setStyleSheet(
        "QPushButton {"
        "font-size: 18px;"
        "background-color: #8e44ad;"
        "color: white;"
        "border-radius: 10px;"
        "}"
        "QPushButton:hover {"
        "background-color: #71368a;"
        "}"
        );
    layout->addWidget(helpButton, 0, Qt::AlignHCenter);

    layout->addSpacerItem(new QSpacerItem(20, 80, QSizePolicy::Minimum, QSizePolicy::Expanding));

    // Help Window (Hidden initially)
    helpWindow = new QWidget(this, Qt::Dialog);
    helpWindow->setFixedSize(400, 300);
    helpWindow->setWindowTitle("Help");
    helpWindow->setStyleSheet("background-color: #ecf0f1;");

    QVBoxLayout *helpLayout = new QVBoxLayout(helpWindow);

    QLabel *helpText = new QLabel("Tactical Monsters is a turn-based strategy game.\n\n"
                                  "- Click on 'Gallery' to view available agents.\n"
                                  "- Click on 'Start an Async PVP Game' to start a match.\n\n"
                                  "Good luck!", helpWindow);
    helpText->setWordWrap(true);
    helpText->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    helpLayout->addWidget(helpText);

    QPushButton *closeHelpBtn = new QPushButton("Close", helpWindow);
    closeHelpBtn->setFixedSize(100, 40);
    closeHelpBtn->setStyleSheet(
        "QPushButton {"
        "background-color: #e67e22;"
        "color: white;"
        "border-radius: 10px;"
        "}"
        "QPushButton:hover {"
        "background-color: #d35400;"
        "}"
        );
    helpLayout->addWidget(closeHelpBtn, 0, Qt::AlignCenter);

    // Connections
    connect(galleryButton, &QPushButton::clicked, this, &MainMenu::openGalleryPage);
    connect(startGameButton, &QPushButton::clicked, this, &MainMenu::openPlayerSetupPage);
    //connect(startGameButton, &QPushButton::clicked, this, &MainMenu::openGamePlayPage);

    connect(helpButton, &QPushButton::clicked, this, &MainMenu::openHelpWindow);
    connect(closeHelpBtn, &QPushButton::clicked, this, &MainMenu::closeHelpWindow);

    // Fade-in animations
    auto fadeIn = [](QWidget* widget) {
        QGraphicsOpacityEffect *effect = new QGraphicsOpacityEffect(widget);
        widget->setGraphicsEffect(effect);
        QPropertyAnimation *anim = new QPropertyAnimation(effect, "opacity");
        anim->setDuration(1200);
        anim->setStartValue(0);
        anim->setEndValue(1);
        anim->start(QPropertyAnimation::DeleteWhenStopped);
    };

    fadeIn(galleryButton);
    fadeIn(startGameButton);
    fadeIn(helpButton);
}

MainMenu::~MainMenu()
{
}

void MainMenu::openGalleryPage()
{
    GalleryPage *gallery = new GalleryPage();
    gallery->show();
    this->close();
}

void MainMenu::openPlayerSetupPage()
{
    PlayerSetupPage *setupPage = new PlayerSetupPage();
    setupPage->show();
    this->close();
}

void MainMenu::openHelpWindow()
{
    helpWindow->show();
}

void MainMenu::closeHelpWindow()
{
    helpWindow->hide();
}

// void MainMenu::openGamePlayPage()
// {
//     gameplayPage = new GamePlayPage();
//     gameplayPage->show();
//     this->close();
// }
