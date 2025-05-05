#ifndef MAINMENU_H
#define MAINMENU_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QPropertyAnimation>
#include "gameplaypage.h"


class MainMenu : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainMenu(QWidget *parent = nullptr);
    ~MainMenu();

private slots:
    void openGalleryPage();
    void openPlayerSetupPage();
    void openHelpWindow();
    void closeHelpWindow();
    // void openGamePlayPage();

private:
    QPushButton *galleryButton;
    QPushButton *startGameButton;
    QPushButton *helpButton;
    QWidget *helpWindow;
    GamePlayPage* gameplayPage = nullptr;

};

#endif // MAINMENU_H
