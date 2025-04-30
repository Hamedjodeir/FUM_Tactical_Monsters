#ifndef GAMEPLAYPAGE_H
#define GAMEPLAYPAGE_H

#include <QWidget>
#include <QString>

namespace Ui {
class GamePlayPage;
}

class GamePlayPage : public QWidget
{
    Q_OBJECT

public:
    explicit GamePlayPage(const QString& player1, const QString& player2, QWidget *parent = nullptr);
    ~GamePlayPage();

private:
    Ui::GamePlayPage *ui;
};

#endif // GAMEPLAYPAGE_H
