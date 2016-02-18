/********************************************************************************
** Form generated from reading UI file 'circledrawer.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CIRCLEDRAWER_H
#define UI_CIRCLEDRAWER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CircleDrawerClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *CircleDrawerClass)
    {
        if (CircleDrawerClass->objectName().isEmpty())
            CircleDrawerClass->setObjectName(QStringLiteral("CircleDrawerClass"));
        CircleDrawerClass->resize(600, 400);
        menuBar = new QMenuBar(CircleDrawerClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        CircleDrawerClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(CircleDrawerClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        CircleDrawerClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(CircleDrawerClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        CircleDrawerClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(CircleDrawerClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        CircleDrawerClass->setStatusBar(statusBar);

        retranslateUi(CircleDrawerClass);

        QMetaObject::connectSlotsByName(CircleDrawerClass);
    } // setupUi

    void retranslateUi(QMainWindow *CircleDrawerClass)
    {
        CircleDrawerClass->setWindowTitle(QApplication::translate("CircleDrawerClass", "CircleDrawer", 0));
    } // retranslateUi

};

namespace Ui {
    class CircleDrawerClass: public Ui_CircleDrawerClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CIRCLEDRAWER_H
