/********************************************************************************
** Form generated from reading UI file 'gameplaypage.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GAMEPLAYPAGE_H
#define UI_GAMEPLAYPAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GamePlayPage
{
public:
    QHBoxLayout *mainHorizontalLayout;
    QFrame *leftPanel;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QGraphicsView *graphicsView;
    QFrame *rightPanel;

    void setupUi(QWidget *GamePlayPage)
    {
        if (GamePlayPage->objectName().isEmpty())
            GamePlayPage->setObjectName("GamePlayPage");
        GamePlayPage->resize(1350, 700);
        mainHorizontalLayout = new QHBoxLayout(GamePlayPage);
        mainHorizontalLayout->setObjectName("mainHorizontalLayout");
        leftPanel = new QFrame(GamePlayPage);
        leftPanel->setObjectName("leftPanel");
        leftPanel->setMinimumSize(QSize(160, 0));
        leftPanel->setMaximumSize(QSize(160, 16777215));
        leftPanel->setStyleSheet(QString::fromUtf8("background-color: #d2b48c;"));
        leftPanel->setFrameShape(QFrame::StyledPanel);
        leftPanel->setFrameShadow(QFrame::Raised);

        mainHorizontalLayout->addWidget(leftPanel);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");

        verticalLayout->addLayout(horizontalLayout);

        graphicsView = new QGraphicsView(GamePlayPage);
        graphicsView->setObjectName("graphicsView");

        verticalLayout->addWidget(graphicsView);


        mainHorizontalLayout->addLayout(verticalLayout);

        rightPanel = new QFrame(GamePlayPage);
        rightPanel->setObjectName("rightPanel");
        rightPanel->setMinimumSize(QSize(160, 0));
        rightPanel->setMaximumSize(QSize(160, 16777215));
        rightPanel->setStyleSheet(QString::fromUtf8("background-color: #d2b48c;"));
        rightPanel->setFrameShape(QFrame::StyledPanel);
        rightPanel->setFrameShadow(QFrame::Raised);

        mainHorizontalLayout->addWidget(rightPanel);


        retranslateUi(GamePlayPage);

        QMetaObject::connectSlotsByName(GamePlayPage);
    } // setupUi

    void retranslateUi(QWidget *GamePlayPage)
    {
        (void)GamePlayPage;
    } // retranslateUi

};

namespace Ui {
    class GamePlayPage: public Ui_GamePlayPage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GAMEPLAYPAGE_H
