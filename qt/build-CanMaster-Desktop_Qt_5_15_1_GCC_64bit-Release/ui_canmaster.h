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
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QListView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CanMaster
{
public:
    QWidget *centralwidget;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QWidget *horizontalLayoutWidget_2;
    QHBoxLayout *horizontalLayout_2;
    QListView *lvData;
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
        horizontalLayoutWidget = new QWidget(centralwidget);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(0, 0, 181, 531));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayoutWidget_2 = new QWidget(centralwidget);
        horizontalLayoutWidget_2->setObjectName(QString::fromUtf8("horizontalLayoutWidget_2"));
        horizontalLayoutWidget_2->setGeometry(QRect(180, 0, 611, 531));
        horizontalLayout_2 = new QHBoxLayout(horizontalLayoutWidget_2);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        lvData = new QListView(horizontalLayoutWidget_2);
        lvData->setObjectName(QString::fromUtf8("lvData"));

        horizontalLayout_2->addWidget(lvData);

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

        QMetaObject::connectSlotsByName(CanMaster);
    } // setupUi

    void retranslateUi(QMainWindow *CanMaster)
    {
        CanMaster->setWindowTitle(QCoreApplication::translate("CanMaster", "CanMaster", nullptr));
        toolBar->setWindowTitle(QCoreApplication::translate("CanMaster", "toolBar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CanMaster: public Ui_CanMaster {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CANMASTER_H
