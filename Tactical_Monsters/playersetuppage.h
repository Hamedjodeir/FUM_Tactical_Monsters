#ifndef PLAYERSETUPPAGE_H
#define PLAYERSETUPPAGE_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QPropertyAnimation>

class PlayerSetupPage : public QWidget {
    Q_OBJECT

public:
    explicit PlayerSetupPage(QWidget *parent = nullptr);

private slots:
    void startGame();

private:
    QLineEdit* player1Input;
    QLineEdit* player2Input;
    QPushButton* startButton;
    QPropertyAnimation* fadeInAnimation;
};

#endif // PLAYERSETUPPAGE_H
