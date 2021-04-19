/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QTabWidget *tabWidget;
    QWidget *tab;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *cls_set;
    QPushButton *cls_ls;
    QPushButton *cls_rm;
    QWidget *tab_2;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *veg_set;
    QPushButton *veg_ls;
    QPushButton *veg_rm;
    QWidget *tab_3;
    QWidget *layoutWidget_2;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *job_set;
    QPushButton *job_ls;
    QPushButton *job_rm;
    QWidget *tab_4;
    QWidget *layoutWidget_3;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *rep1;
    QPushButton *rep2;
    QPushButton *rep3;
    QTableWidget *tableWidget;
    QPushButton *pushButton;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(452, 757);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setGeometry(QRect(10, 10, 421, 111));
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        layoutWidget = new QWidget(tab);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 10, 391, 51));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        cls_set = new QPushButton(layoutWidget);
        cls_set->setObjectName(QStringLiteral("cls_set"));

        horizontalLayout->addWidget(cls_set);

        cls_ls = new QPushButton(layoutWidget);
        cls_ls->setObjectName(QStringLiteral("cls_ls"));

        horizontalLayout->addWidget(cls_ls);

        cls_rm = new QPushButton(layoutWidget);
        cls_rm->setObjectName(QStringLiteral("cls_rm"));

        horizontalLayout->addWidget(cls_rm);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        layoutWidget1 = new QWidget(tab_2);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(10, 10, 391, 51));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget1);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        veg_set = new QPushButton(layoutWidget1);
        veg_set->setObjectName(QStringLiteral("veg_set"));

        horizontalLayout_2->addWidget(veg_set);

        veg_ls = new QPushButton(layoutWidget1);
        veg_ls->setObjectName(QStringLiteral("veg_ls"));

        horizontalLayout_2->addWidget(veg_ls);

        veg_rm = new QPushButton(layoutWidget1);
        veg_rm->setObjectName(QStringLiteral("veg_rm"));

        horizontalLayout_2->addWidget(veg_rm);

        tabWidget->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QStringLiteral("tab_3"));
        layoutWidget_2 = new QWidget(tab_3);
        layoutWidget_2->setObjectName(QStringLiteral("layoutWidget_2"));
        layoutWidget_2->setGeometry(QRect(10, 10, 391, 51));
        horizontalLayout_3 = new QHBoxLayout(layoutWidget_2);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        job_set = new QPushButton(layoutWidget_2);
        job_set->setObjectName(QStringLiteral("job_set"));

        horizontalLayout_3->addWidget(job_set);

        job_ls = new QPushButton(layoutWidget_2);
        job_ls->setObjectName(QStringLiteral("job_ls"));

        horizontalLayout_3->addWidget(job_ls);

        job_rm = new QPushButton(layoutWidget_2);
        job_rm->setObjectName(QStringLiteral("job_rm"));

        horizontalLayout_3->addWidget(job_rm);

        tabWidget->addTab(tab_3, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName(QStringLiteral("tab_4"));
        layoutWidget_3 = new QWidget(tab_4);
        layoutWidget_3->setObjectName(QStringLiteral("layoutWidget_3"));
        layoutWidget_3->setGeometry(QRect(10, 10, 391, 51));
        horizontalLayout_4 = new QHBoxLayout(layoutWidget_3);
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        rep1 = new QPushButton(layoutWidget_3);
        rep1->setObjectName(QStringLiteral("rep1"));

        horizontalLayout_4->addWidget(rep1);

        rep2 = new QPushButton(layoutWidget_3);
        rep2->setObjectName(QStringLiteral("rep2"));

        horizontalLayout_4->addWidget(rep2);

        rep3 = new QPushButton(layoutWidget_3);
        rep3->setObjectName(QStringLiteral("rep3"));

        horizontalLayout_4->addWidget(rep3);

        tabWidget->addTab(tab_4, QString());
        tableWidget = new QTableWidget(centralWidget);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));
        tableWidget->setGeometry(QRect(10, 130, 431, 601));
        tableWidget->horizontalHeader()->setVisible(false);
        tableWidget->verticalHeader()->setVisible(true);
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(340, 690, 84, 28));
        MainWindow->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        cls_set->setText(QApplication::translate("MainWindow", "Set/Add", Q_NULLPTR));
        cls_ls->setText(QApplication::translate("MainWindow", "Print", Q_NULLPTR));
        cls_rm->setText(QApplication::translate("MainWindow", "Remove", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("MainWindow", "Classes", Q_NULLPTR));
        veg_set->setText(QApplication::translate("MainWindow", "Set/Add", Q_NULLPTR));
        veg_ls->setText(QApplication::translate("MainWindow", "Print", Q_NULLPTR));
        veg_rm->setText(QApplication::translate("MainWindow", "Remove", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("MainWindow", "Vegetables", Q_NULLPTR));
        job_set->setText(QApplication::translate("MainWindow", "Set/Add", Q_NULLPTR));
        job_ls->setText(QApplication::translate("MainWindow", "Print", Q_NULLPTR));
        job_rm->setText(QApplication::translate("MainWindow", "Remove", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QApplication::translate("MainWindow", "Jobs", Q_NULLPTR));
        rep1->setText(QApplication::translate("MainWindow", "Jobs by class", Q_NULLPTR));
        rep2->setText(QApplication::translate("MainWindow", "Jobs by year", Q_NULLPTR));
        rep3->setText(QApplication::translate("MainWindow", "Weight per class", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_4), QApplication::translate("MainWindow", "Reports", Q_NULLPTR));
        pushButton->setText(QApplication::translate("MainWindow", "DEbug", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
