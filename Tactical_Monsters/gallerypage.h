#ifndef GALLERYPAGE_H
#define GALLERYPAGE_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>
#include <QVector>

class GalleryPage : public QMainWindow
{
    Q_OBJECT

public:
    explicit GalleryPage(QWidget *parent = nullptr);
    ~GalleryPage();

private slots:
    void goBackToMainMenu();

private:
    void createAgentCards();
    void centerWindow();

    QPushButton *backButton;
    QLabel *titleLabel;
    QVector<QWidget*> agentCards;
    QParallelAnimationGroup *animationGroup;
};

#endif // GALLERYPAGE_H
