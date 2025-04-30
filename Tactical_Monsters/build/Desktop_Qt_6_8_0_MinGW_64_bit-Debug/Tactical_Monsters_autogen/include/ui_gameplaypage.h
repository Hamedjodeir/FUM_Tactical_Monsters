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
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GamePlayPage
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayoutTop;
    QLabel *labelPlayer1;
    QSpacerItem *horizontalSpacer;
    QLabel *labelPlayer2;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *GamePlayPage)
    {
        if (GamePlayPage->objectName().isEmpty())
            GamePlayPage->setObjectName("GamePlayPage");
        GamePlayPage->resize(1350, 700);
        verticalLayout = new QVBoxLayout(GamePlayPage);
        verticalLayout->setObjectName("verticalLayout");
        horizontalLayoutTop = new QHBoxLayout();
        horizontalLayoutTop->setObjectName("horizontalLayoutTop");
        labelPlayer1 = new QLabel(GamePlayPage);
        labelPlayer1->setObjectName("labelPlayer1");
        labelPlayer1->setStyleSheet(QString::fromUtf8("font-size: 20px; font-weight: bold; color: #2c3e50; padding: 10px;"));

        horizontalLayoutTop->addWidget(labelPlayer1);

        horizontalSpacer = new QSpacerItem(1000, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayoutTop->addItem(horizontalSpacer);

        labelPlayer2 = new QLabel(GamePlayPage);
        labelPlayer2->setObjectName("labelPlayer2");
        labelPlayer2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        labelPlayer2->setStyleSheet(QString::fromUtf8("font-size: 20px; font-weight: bold; color: #2c3e50; padding: 10px;"));

        horizontalLayoutTop->addWidget(labelPlayer2);


        verticalLayout->addLayout(horizontalLayoutTop);

        verticalSpacer = new QSpacerItem(20, 500, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        verticalLayout->setStretch(1, 1);

        retranslateUi(GamePlayPage);

        QMetaObject::connectSlotsByName(GamePlayPage);
    } // setupUi

    void retranslateUi(QWidget *GamePlayPage)
    {
        GamePlayPage->setWindowTitle(QCoreApplication::translate("GamePlayPage", "Tactical Monsters - Gameplay", nullptr));
        labelPlayer1->setText(QCoreApplication::translate("GamePlayPage", "Player 1", nullptr));
        labelPlayer2->setText(QCoreApplication::translate("GamePlayPage", "Player 2", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GamePlayPage: public Ui_GamePlayPage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GAMEPLAYPAGE_H
