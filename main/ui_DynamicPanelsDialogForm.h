/********************************************************************************
** Form generated from reading UI file 'DynamicPanelsDialogForm.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DYNAMICPANELSDIALOGFORM_H
#define UI_DYNAMICPANELSDIALOGFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QDateTimeEdit>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFontComboBox>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTimeEdit>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_DialogForm
{
public:
    QVBoxLayout *verticalLayout;
    QVBoxLayout *verticalLayout_1;
    QTimeEdit *timeEdit;
    QDateEdit *dateEdit;
    QDateTimeEdit *dateTimeEdit;
    QFontComboBox *fontComboBox;
    QSpacerItem *verticalSpacer;

    void setupUi(QDialog *DialogForm)
    {
        if (DialogForm->objectName().isEmpty())
            DialogForm->setObjectName(QString::fromUtf8("DialogForm"));
        DialogForm->resize(200, 483);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(DialogForm->sizePolicy().hasHeightForWidth());
        DialogForm->setSizePolicy(sizePolicy);
        DialogForm->setModal(false);
        verticalLayout = new QVBoxLayout(DialogForm);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout_1 = new QVBoxLayout();
        verticalLayout_1->setObjectName(QString::fromUtf8("verticalLayout_1"));
        timeEdit = new QTimeEdit(DialogForm);
        timeEdit->setObjectName(QString::fromUtf8("timeEdit"));
        QSizePolicy sizePolicy1(QSizePolicy::Ignored, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(timeEdit->sizePolicy().hasHeightForWidth());
        timeEdit->setSizePolicy(sizePolicy1);

        verticalLayout_1->addWidget(timeEdit);

        dateEdit = new QDateEdit(DialogForm);
        dateEdit->setObjectName(QString::fromUtf8("dateEdit"));
        sizePolicy1.setHeightForWidth(dateEdit->sizePolicy().hasHeightForWidth());
        dateEdit->setSizePolicy(sizePolicy1);

        verticalLayout_1->addWidget(dateEdit);

        dateTimeEdit = new QDateTimeEdit(DialogForm);
        dateTimeEdit->setObjectName(QString::fromUtf8("dateTimeEdit"));
        sizePolicy1.setHeightForWidth(dateTimeEdit->sizePolicy().hasHeightForWidth());
        dateTimeEdit->setSizePolicy(sizePolicy1);

        verticalLayout_1->addWidget(dateTimeEdit);

        fontComboBox = new QFontComboBox(DialogForm);
        fontComboBox->setObjectName(QString::fromUtf8("fontComboBox"));
        sizePolicy1.setHeightForWidth(fontComboBox->sizePolicy().hasHeightForWidth());
        fontComboBox->setSizePolicy(sizePolicy1);

        verticalLayout_1->addWidget(fontComboBox);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_1->addItem(verticalSpacer);


        verticalLayout->addLayout(verticalLayout_1);


        retranslateUi(DialogForm);

        QMetaObject::connectSlotsByName(DialogForm);
    } // setupUi

    void retranslateUi(QDialog *DialogForm)
    {
        DialogForm->setWindowTitle(QCoreApplication::translate("DialogForm", "Dialog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DialogForm: public Ui_DialogForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DYNAMICPANELSDIALOGFORM_H
