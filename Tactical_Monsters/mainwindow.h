#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QPropertyAnimation>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onContinueButtonClicked();

private:
    QLabel* welcomeLabel;
    QPushButton* continueButton;
    QPropertyAnimation* welcomeAnimation;
    QPropertyAnimation* buttonAnimation;
};

#endif // MAINWINDOW_H
