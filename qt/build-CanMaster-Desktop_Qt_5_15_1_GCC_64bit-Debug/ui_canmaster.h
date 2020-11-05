/********************************************************************************
** Form generated from reading UI file 'canmaster.ui'
**
** Created by: Qt User Interface Compiler version 5.15.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CANMASTER_H
#define UI_CANMASTER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CanMaster
{
public:
    QWidget *centralwidget;
    QLCDNumber *lcdNumber;
    QProgressBar *progressBar;
    QPushButton *btnMinus;
    QPushButton *btnPlus;
    QMenuBar *menubar;
    QStatusBar *statusbar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *CanMaster)
    {
        if (CanMaster->objectName().isEmpty())
            CanMaster->setObjectName(QString::fromUtf8("CanMaster"));
        CanMaster->resize(800, 600);
        centralwidget = new QWidget(CanMaster);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        lcdNumber = new QLCDNumber(centralwidget);
        lcdNumber->setObjectName(QString::fromUtf8("lcdNumber"));
        lcdNumber->setGeometry(QRect(170, 110, 64, 23));
        lcdNumber->setProperty("intValue", QVariant(1));
        progressBar = new QProgressBar(centralwidget);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setGeometry(QRect(170, 140, 241, 23));
        progressBar->setValue(24);
        btnMinus = new QPushButton(centralwidget);
        btnMinus->setObjectName(QString::fromUtf8("btnMinus"));
        btnMinus->setGeometry(QRect(200, 170, 80, 24));
        btnPlus = new QPushButton(centralwidget);
        btnPlus->setObjectName(QString::fromUtf8("btnPlus"));
        btnPlus->setGeometry(QRect(300, 170, 80, 24));
        CanMaster->setCentralWidget(centralwidget);
        menubar = new QMenuBar(CanMaster);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 21));
        CanMaster->setMenuBar(menubar);
        statusbar = new QStatusBar(CanMaster);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        CanMaster->setStatusBar(statusbar);
        toolBar = new QToolBar(CanMaster);
        toolBar->setObjectName(QString::fromUtf8("toolBar"));
        CanMaster->addToolBar(Qt::TopToolBarArea, toolBar);

        retranslateUi(CanMaster);
        QObject::connect(btnMinus, SIGNAL(clicked()), lcdNumber, SLOT(setDecMode()));
        QObject::connect(btnPlus, SIGNAL(clicked()), lcdNumber, SLOT(setDecMode()));
        QObject::connect(lcdNumber, SIGNAL(overflow()), progressBar, SLOT(reset()));

        QMetaObject::connectSlotsByName(CanMaster);
    } // setupUi

    void retranslateUi(QMainWindow *CanMaster)
    {
        CanMaster->setWindowTitle(QCoreApplication::translate("CanMaster", "CanMaster", nullptr));
        btnMinus->setText(QCoreApplication::translate("CanMaster", "<<", nullptr));
        btnPlus->setText(QCoreApplication::translate("CanMaster", ">>", nullptr));
        toolBar->setWindowTitle(QCoreApplication::translate("CanMaster", "toolBar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CanMaster: public Ui_CanMaster {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CANMASTER_H
