/********************************************************************************
** Form generated from reading UI file 'gallerypage.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GALLERYPAGE_H
#define UI_GALLERYPAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GalleryPage
{
public:

    void setupUi(QWidget *GalleryPage)
    {
        if (GalleryPage->objectName().isEmpty())
            GalleryPage->setObjectName("GalleryPage");
        GalleryPage->resize(400, 300);

        retranslateUi(GalleryPage);

        QMetaObject::connectSlotsByName(GalleryPage);
    } // setupUi

    void retranslateUi(QWidget *GalleryPage)
    {
        GalleryPage->setWindowTitle(QCoreApplication::translate("GalleryPage", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GalleryPage: public Ui_GalleryPage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GALLERYPAGE_H
