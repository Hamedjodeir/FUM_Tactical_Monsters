#include "gallerypage.h"
#include "mainmenu.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTimer>
#include <QScreen>
#include <QGuiApplication>

GalleryPage::GalleryPage(QWidget *parent)
    : QMainWindow(parent)
{
    this->setWindowTitle("Gallery - Tactical Monsters");
    this->resize(1200, 700);
    centerWindow();
    this->setStyleSheet("background-color: #E28743;"); // New base color

    // Back bttn
    backButton = new QPushButton("Back", this);
    backButton->setStyleSheet("QPushButton {"
                              "background-color: #8B4513;"
                              "color: white;"
                              "font: bold 18px;"
                              "border: 2px solid white;"
                              "border-radius: 8px;"
                              "padding: 6px;"
                              "}"
                              "QPushButton:hover {"
                              "background-color: white;"
                              "color: black;"
                              "}");
    backButton->setGeometry(20, 20, 100, 40);
    connect(backButton, &QPushButton::clicked, this, &GalleryPage::goBackToMainMenu);

    // Title
    titleLabel = new QLabel("Gallery", this);
    titleLabel->setStyleSheet("QLabel {"
                              "color: white;"
                              "font: bold 32px;"
                              "}");
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setGeometry(0, 70, width(), 50);

    createAgentCards();

    // animation
    QTimer::singleShot(100, [this]() {
        animationGroup->start();
    });
}

GalleryPage::~GalleryPage()
{
}

void GalleryPage::centerWindow()
{
    QRect screenGeometry = QGuiApplication::primaryScreen()->geometry();
    int screenWidth = screenGeometry.width();
    int x = (screenWidth - width()) / 2;
    int y = 0;
    move(x, y);
}

void GalleryPage::createAgentCards()
{
    // Cardbox
    QWidget *cardsContainer = new QWidget(this);
    cardsContainer->setGeometry(50, 150, 1100, 500);

    QGridLayout *gridLayout = new QGridLayout(cardsContainer);
    gridLayout->setSpacing(30);
    gridLayout->setContentsMargins(0, 0, 0, 0);

    animationGroup = new QParallelAnimationGroup(this);

    int totalCards = 8;

    for (int i = 0; i < totalCards; ++i)
    {
        QWidget *card = new QWidget(cardsContainer);
        card->setFixedSize(200, 250);
        card->setStyleSheet(
            "QWidget {"
            "background-color: #FFA07A;"
            "border-radius: 15px;"
            "border: 3px solid #8B4513;"
            "transition: all 0.3s;"
            "}"
            "QWidget:hover {"
            "transform: scale(1.05);"
            "border: 3px solid white;"
            "}"
            );

        QVBoxLayout *cardLayout = new QVBoxLayout(card);

        QLabel *agentImage = new QLabel(card);
        agentImage->setFixedSize(180, 180);
        agentImage->setStyleSheet(
            "QLabel {"
            "background-color: #CD853F;"
            "border-radius: 10px;"
            "color: white;"
            "font: bold 16px;"
            "}");
        agentImage->setAlignment(Qt::AlignCenter);
        agentImage->setText("Coming Soon");

        QLabel *agentName = new QLabel("Agent Name", card);
        agentName->setStyleSheet(
            "QLabel {"
            "color: white;"
            "font: bold 14px;"
            "}");
        agentName->setAlignment(Qt::AlignCenter);

        cardLayout->addWidget(agentImage);
        cardLayout->addWidget(agentName);

        int row = i / 4;
        int col = i % 4;
        gridLayout->addWidget(card, row, col);

        agentCards.append(card);
    }

    // * animation
    QTimer::singleShot(50, [this]() {
        for (auto card : agentCards)
        {
            QRect endGeometry = card->geometry();
            QRect startGeometry(endGeometry.x() - 300, endGeometry.y(), endGeometry.width(), endGeometry.height());

            QPropertyAnimation *anim = new QPropertyAnimation(card, "geometry");
            anim->setDuration(800);
            anim->setStartValue(startGeometry);
            anim->setEndValue(endGeometry);
            anim->setEasingCurve(QEasingCurve::OutBack);

            animationGroup->addAnimation(anim);
        }
    });
}

void GalleryPage::goBackToMainMenu()
{
    MainMenu *mainMenu = new MainMenu();
    mainMenu->show();
    this->close();
}
