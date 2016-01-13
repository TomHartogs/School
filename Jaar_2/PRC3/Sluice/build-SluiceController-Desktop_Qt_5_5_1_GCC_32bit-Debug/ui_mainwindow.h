/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QLabel *label_4;
    QLabel *label_2;
    QPushButton *SchutSluice2;
    QLabel *label;
    QPushButton *SchutSluice3;
    QPushButton *SchutSluice4;
    QLabel *label_3;
    QPushButton *SchutSluice1;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(446, 96);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(360, 10, 67, 17));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(140, 10, 67, 17));
        SchutSluice2 = new QPushButton(centralwidget);
        SchutSluice2->setObjectName(QStringLiteral("SchutSluice2"));
        SchutSluice2->setGeometry(QRect(120, 30, 89, 25));
        label = new QLabel(centralwidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(30, 10, 67, 17));
        SchutSluice3 = new QPushButton(centralwidget);
        SchutSluice3->setObjectName(QStringLiteral("SchutSluice3"));
        SchutSluice3->setGeometry(QRect(230, 30, 89, 25));
        SchutSluice4 = new QPushButton(centralwidget);
        SchutSluice4->setObjectName(QStringLiteral("SchutSluice4"));
        SchutSluice4->setGeometry(QRect(340, 30, 89, 25));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(250, 10, 67, 17));
        SchutSluice1 = new QPushButton(centralwidget);
        SchutSluice1->setObjectName(QStringLiteral("SchutSluice1"));
        SchutSluice1->setGeometry(QRect(10, 30, 89, 25));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 446, 22));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        label_4->setText(QApplication::translate("MainWindow", "Sluice 4", 0));
        label_2->setText(QApplication::translate("MainWindow", "Sluice 2", 0));
        SchutSluice2->setText(QApplication::translate("MainWindow", "Schut", 0));
        label->setText(QApplication::translate("MainWindow", "Sluice 1", 0));
        SchutSluice3->setText(QApplication::translate("MainWindow", "Schut", 0));
        SchutSluice4->setText(QApplication::translate("MainWindow", "Schut", 0));
        label_3->setText(QApplication::translate("MainWindow", "Sluice 3", 0));
        SchutSluice1->setText(QApplication::translate("MainWindow", "Schut", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
