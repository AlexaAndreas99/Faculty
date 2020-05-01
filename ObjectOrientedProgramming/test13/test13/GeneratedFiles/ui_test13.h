/********************************************************************************
** Form generated from reading UI file 'test13.ui'
**
** Created by: Qt User Interface Compiler version 5.12.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TEST13_H
#define UI_TEST13_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_test13Class
{
public:
    QWidget *centralWidget;
    QListWidget *weatherListWidget;
    QLineEdit *filterInput;
    QLineEdit *descInput;
    QPushButton *totalButton;
    QLabel *totalLabel;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *test13Class)
    {
        if (test13Class->objectName().isEmpty())
            test13Class->setObjectName(QString::fromUtf8("test13Class"));
        test13Class->resize(600, 400);
        centralWidget = new QWidget(test13Class);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        weatherListWidget = new QListWidget(centralWidget);
        weatherListWidget->setObjectName(QString::fromUtf8("weatherListWidget"));
        weatherListWidget->setGeometry(QRect(0, 40, 256, 192));
        filterInput = new QLineEdit(centralWidget);
        filterInput->setObjectName(QString::fromUtf8("filterInput"));
        filterInput->setGeometry(QRect(0, 20, 251, 22));
        descInput = new QLineEdit(centralWidget);
        descInput->setObjectName(QString::fromUtf8("descInput"));
        descInput->setGeometry(QRect(290, 80, 113, 22));
        totalButton = new QPushButton(centralWidget);
        totalButton->setObjectName(QString::fromUtf8("totalButton"));
        totalButton->setGeometry(QRect(290, 120, 93, 28));
        totalLabel = new QLabel(centralWidget);
        totalLabel->setObjectName(QString::fromUtf8("totalLabel"));
        totalLabel->setGeometry(QRect(470, 100, 71, 51));
        test13Class->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(test13Class);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 600, 26));
        test13Class->setMenuBar(menuBar);
        mainToolBar = new QToolBar(test13Class);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        test13Class->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(test13Class);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        test13Class->setStatusBar(statusBar);

        retranslateUi(test13Class);

        QMetaObject::connectSlotsByName(test13Class);
    } // setupUi

    void retranslateUi(QMainWindow *test13Class)
    {
        test13Class->setWindowTitle(QApplication::translate("test13Class", "test13", nullptr));
        totalButton->setText(QApplication::translate("test13Class", "compute ", nullptr));
        totalLabel->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class test13Class: public Ui_test13Class {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TEST13_H
