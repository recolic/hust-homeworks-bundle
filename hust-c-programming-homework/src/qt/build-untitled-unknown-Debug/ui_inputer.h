/********************************************************************************
** Form generated from reading UI file 'inputer.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INPUTER_H
#define UI_INPUTER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Inputer
{
public:
    QDialogButtonBox *buttonBox;
    QWidget *formLayoutWidget;
    QFormLayout *formLayout;
    QLabel *l1;
    QLineEdit *e1;
    QLineEdit *e3;
    QLabel *l3;
    QLabel *l4;
    QLineEdit *e4;
    QLabel *l2;
    QLineEdit *e2;
    QLineEdit *e5;
    QLabel *l5;

    void setupUi(QDialog *Inputer)
    {
        if (Inputer->objectName().isEmpty())
            Inputer->setObjectName(QStringLiteral("Inputer"));
        Inputer->resize(321, 259);
        buttonBox = new QDialogButtonBox(Inputer);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(140, 220, 171, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        formLayoutWidget = new QWidget(Inputer);
        formLayoutWidget->setObjectName(QStringLiteral("formLayoutWidget"));
        formLayoutWidget->setGeometry(QRect(10, 10, 301, 201));
        formLayout = new QFormLayout(formLayoutWidget);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        formLayout->setContentsMargins(0, 0, 0, 0);
        l1 = new QLabel(formLayoutWidget);
        l1->setObjectName(QStringLiteral("l1"));

        formLayout->setWidget(1, QFormLayout::LabelRole, l1);

        e1 = new QLineEdit(formLayoutWidget);
        e1->setObjectName(QStringLiteral("e1"));

        formLayout->setWidget(1, QFormLayout::FieldRole, e1);

        e3 = new QLineEdit(formLayoutWidget);
        e3->setObjectName(QStringLiteral("e3"));

        formLayout->setWidget(4, QFormLayout::FieldRole, e3);

        l3 = new QLabel(formLayoutWidget);
        l3->setObjectName(QStringLiteral("l3"));

        formLayout->setWidget(4, QFormLayout::LabelRole, l3);

        l4 = new QLabel(formLayoutWidget);
        l4->setObjectName(QStringLiteral("l4"));

        formLayout->setWidget(5, QFormLayout::LabelRole, l4);

        e4 = new QLineEdit(formLayoutWidget);
        e4->setObjectName(QStringLiteral("e4"));

        formLayout->setWidget(5, QFormLayout::FieldRole, e4);

        l2 = new QLabel(formLayoutWidget);
        l2->setObjectName(QStringLiteral("l2"));

        formLayout->setWidget(3, QFormLayout::LabelRole, l2);

        e2 = new QLineEdit(formLayoutWidget);
        e2->setObjectName(QStringLiteral("e2"));
        e2->setEnabled(true);

        formLayout->setWidget(3, QFormLayout::FieldRole, e2);

        e5 = new QLineEdit(formLayoutWidget);
        e5->setObjectName(QStringLiteral("e5"));

        formLayout->setWidget(6, QFormLayout::FieldRole, e5);

        l5 = new QLabel(formLayoutWidget);
        l5->setObjectName(QStringLiteral("l5"));

        formLayout->setWidget(6, QFormLayout::LabelRole, l5);


        retranslateUi(Inputer);
        QObject::connect(buttonBox, SIGNAL(accepted()), Inputer, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), Inputer, SLOT(reject()));

        QMetaObject::connectSlotsByName(Inputer);
    } // setupUi

    void retranslateUi(QDialog *Inputer)
    {
        Inputer->setWindowTitle(QApplication::translate("Inputer", "Dialog", Q_NULLPTR));
        l1->setText(QApplication::translate("Inputer", "TextLabel", Q_NULLPTR));
        l3->setText(QApplication::translate("Inputer", "TextLabel", Q_NULLPTR));
        l4->setText(QApplication::translate("Inputer", "TextLabel", Q_NULLPTR));
        l2->setText(QApplication::translate("Inputer", "TextLabel", Q_NULLPTR));
        l5->setText(QApplication::translate("Inputer", "TextLabel", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Inputer: public Ui_Inputer {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INPUTER_H
