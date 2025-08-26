#include "gallerypage.h"
#include "mainmenu.h"
#include "agentBuild.h"   // <-- include the agent definitions
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTimer>
#include <QScreen>
#include <QGuiApplication>
#include <QGridLayout>
#include <QLabel>
#include <QPropertyAnimation>
#include <QScrollArea>


GalleryPage::GalleryPage(QWidget *parent)
    : QMainWindow(parent)
{
    this->setWindowTitle("Gallery - Tactical Monsters");
    this->resize(1200, 700);
    centerWindow();
    this->setStyleSheet("background-color: #E28743;"); // New base color

    // Back button
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
    // Get agents
    auto allAgents = AgentBuild::createAllAgents();

    // Scroll area
    QScrollArea *scrollArea = new QScrollArea(this);
    scrollArea->setGeometry(50, 150, 1100, 500);
    scrollArea->setWidgetResizable(true);
    scrollArea->setStyleSheet("background: transparent; border: none;");

    QWidget *container = new QWidget(scrollArea);
    QGridLayout *gridLayout = new QGridLayout(container);
    gridLayout->setSpacing(30);
    gridLayout->setContentsMargins(10, 10, 10, 10);

    scrollArea->setWidget(container);

    animationGroup = new QParallelAnimationGroup(this);

    int i = 0;
    for (auto &agent : allAgents)
    {
        QWidget *card = new QWidget(container);
        card->setFixedSize(200, 250);
        card->setStyleSheet(
            "QWidget {"
            "background-color: #FFA07A;"
            "border-radius: 15px;"
            "border: 3px solid #8B4513;"
            "}"
            "QWidget:hover {"
            "border: 3px solid white;"
            "}"
            );

        QVBoxLayout *cardLayout = new QVBoxLayout(card);

        // Image
        QLabel *agentImage = new QLabel(card);
        agentImage->setFixedSize(180, 160);
        agentImage->setAlignment(Qt::AlignCenter);
        QPixmap pix(agent->getImagePath());
        if (!pix.isNull()) {
            agentImage->setPixmap(pix.scaled(agentImage->size(),
                                             Qt::KeepAspectRatio,
                                             Qt::SmoothTransformation));
        } else {
            agentImage->setText("No Image");
            agentImage->setStyleSheet("QLabel { color: white; font: bold 14px; }");
        }

        // Name
        QLabel *agentName = new QLabel(agent->getName(), card);
        agentName->setAlignment(Qt::AlignCenter);
        agentName->setStyleSheet("QLabel { color: white; font: bold 14px; }");

        // Stats (HP / DMG / Mobility / Range)
        QLabel *agentStats = new QLabel(
            QString("HP: %1\nDMG: %2\nMobility: %3\nRange: %4")
                .arg(agent->getHp())
                .arg(agent->getDmg())
                .arg(agent->getMobility())
                .arg(agent->getAttackRange()),
            card);
        agentStats->setAlignment(Qt::AlignCenter);
        agentStats->setStyleSheet("QLabel { color: white; font: 12px; }");

        cardLayout->addWidget(agentImage);
        cardLayout->addWidget(agentName);
        cardLayout->addWidget(agentStats);

        int row = i / 4;
        int col = i % 4;
        gridLayout->addWidget(card, row, col);

        agentCards.append(card);
        ++i;
    }

    // Optional animation
    QTimer::singleShot(50, [this]() {
        for (auto card : agentCards) {
            QRect endGeometry = card->geometry();
            QRect startGeometry(endGeometry.x() - 300, endGeometry.y(),
                                endGeometry.width(), endGeometry.height());

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
