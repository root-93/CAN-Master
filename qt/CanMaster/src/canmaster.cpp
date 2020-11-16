#include "../inc/canmaster.h"
#include "ui_canmaster.h"
#include "../inc/CanUtils.hpp"
#include <qdebug.h>
#include <QtConcurrent/qtconcurrentrun.h>
#include <QString>



namespace cu = canutils;

CanMaster::CanMaster(QWidget *parent): QMainWindow(parent), ui(new Ui::CanMaster){
    ui->setupUi(this);
    createMenuBar();

    QListView *lv = ui->lvData;
    QTableView *tv = ui->tvData;

    model = new QStringListModel(this);
    QStringList list {};
    model->setStringList(list);
    lv->setModel(model);
    lv->setFont(QFont("Courier", 12));

    tableModel = new TableModel(this);
    tv->setModel(tableModel);

    connectCan();
}


CanMaster::~CanMaster(){
    delete ui;
    *pRunGen = 0;
    *pRunSniff = 0;
}

void CanMaster::updateLvData(){
    QStringList list = model->stringList();
    QCanBusFrame *frame  = new QCanBusFrame();
    while(pDev->framesAvailable()){
        *frame = pDev->readFrame();
        list.append((*frame).toString());
        tableModel->append(frame);
    }



    model->setStringList(list);
    ui->lvData->scrollToBottom();
}


void CanMaster::connectCan() noexcept{
    if(!QCanBus::instance()->plugins().contains(QStringLiteral("socketcan")))
        qFatal("Qcab bus doesn't provide the desired plugin \"socketcan\"");

    pDev = QCanBus::instance()->createDevice(
                                     QStringLiteral("socketcan"),
                                     QStringLiteral("vcan0"),
                                     &errorString);

   if(!pDev)
       qDebug() << errorString;
   else
       pDev->connectDevice();

   connect(pDev, SIGNAL(framesReceived()), this, SLOT(updateLvData()));

   // get available interfaces with availableDevices() to choice interface
}


void CanMaster::createMenuBar() noexcept{
    QMenu* menuProject = new QMenu(tr("Project"), this);
    QMenu* menuCan = new QMenu(tr("Can Utils"), this);
    QMenu* menuTools = new QMenu(tr("Tools"), this);
    QMenu* menuHelp = new QMenu(tr("Help"), this);

    ui->menubar->addMenu(menuProject);
    ui->menubar->addMenu(menuCan);
    ui->menubar->addMenu(menuTools);
    ui->menubar->addMenu(menuHelp);

    menuProject->addAction(tr("new"), this, SLOT(foo()), tr("Ctrl+N"));
    menuProject->addAction(tr("open"), this, SLOT(foo()), tr("Ctrl+O"));
    menuProject->addAction(tr("save"), this, SLOT(foo()), tr("Ctrl+S"));
    menuProject->addAction(tr("save as"), this, SLOT(foo()), tr("Ctrl+Shift+S"));
    menuProject->addAction(tr("exit"), this, SLOT(foo()));

    pCanGenAction = new QAction(tr("gen"), this);
    pCanGenAction->setCheckable(true);
    connect(pCanGenAction, SIGNAL(triggered()), this, SLOT(canGen()));
    menuCan->addAction(pCanGenAction);

    menuCan->addAction(tr("dump"), this, SLOT(foo()));

    pCanSniffAction = new QAction(tr("sniff"), this);
    pCanSniffAction->setCheckable(true);
    connect(pCanSniffAction, SIGNAL(triggered()), this, SLOT(canSniffer()));
    menuCan->addAction(pCanSniffAction);

    menuCan->addAction(tr("player"), this, SLOT(foo()));
    menuCan->addAction(tr("send"), this, SLOT(foo()));

    menuTools->addAction(tr("config"), this, SLOT(foo()));

    menuHelp->addAction(tr("Nobody help you :P"), this, SLOT(foo()));
}

void CanMaster::canGen(){
    if(!pCanGenAction->isChecked()){
        *pRunGen = 0;
    }
    else{
        *pRunGen = 1;

        params[0] = const_cast<char *>("canGen");
        params[1] = const_cast<char *>("vcan0");

        char **ppCanGenArg = params;
        QtConcurrent::run(cu::canGen, 2, ppCanGenArg, pRunGen);
    }
}

void CanMaster::canSniffer(){
    if(!pCanGenAction->isChecked()){
        *pRunSniff = 0;
    }
    else{
        *pRunSniff = 1;

        params[0] = const_cast<char *>("canSniffer");
        params[1] = const_cast<char *>("vcan0");

        char **ppCanGenArg = params;
        QtConcurrent::run(cu::canSniffer, 2, ppCanGenArg, pRunSniff, (void**)&pSniffBuf);
    }
}
