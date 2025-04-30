/********************************************************************************
** Form generated from reading UI file 'playersetuppage.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PLAYERSETUPPAGE_H
#define UI_PLAYERSETUPPAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PlayerSetupPage
{
public:

    void setupUi(QWidget *PlayerSetupPage)
    {
        if (PlayerSetupPage->objectName().isEmpty())
            PlayerSetupPage->setObjectName("PlayerSetupPage");
        PlayerSetupPage->resize(400, 300);

        retranslateUi(PlayerSetupPage);

        QMetaObject::connectSlotsByName(PlayerSetupPage);
    } // setupUi

    void retranslateUi(QWidget *PlayerSetupPage)
    {
        PlayerSetupPage->setWindowTitle(QCoreApplication::translate("PlayerSetupPage", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PlayerSetupPage: public Ui_PlayerSetupPage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PLAYERSETUPPAGE_H
