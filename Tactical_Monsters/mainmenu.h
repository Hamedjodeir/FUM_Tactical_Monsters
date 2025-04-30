#ifndef MAINMENU_H
#define MAINMENU_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QPropertyAnimation>
#include "gameplaypage.h"  // Add this include


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
    void openGamePlayPage();  // Add this new slot

private:
    QPushButton *galleryButton;
    QPushButton *startGameButton;
    QPushButton *helpButton;
    QWidget *helpWindow;
    GamePlayPage* gameplayPage = nullptr;  // Optional: store the page if you want to keep a reference

};

#endif // MAINMENU_H
