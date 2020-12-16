#include "../inc/canmaster.h"
#include "ui_canmaster.h"
#include "../inc/CanUtils.hpp"
#include <qdebug.h>
#include <QtConcurrent/qtconcurrentrun.h>
#include <QString>
#include <QCanBusDevice>

namespace cu = canutils;


CanMaster::CanMaster(QWidget *parent)
    : QMainWindow(parent), _ui(new Ui::CanMaster){

    _ui->setupUi(this);
    _pTableModel = new TableModel(_pStack->getFrames(), this);
    _pFilter = FilterDump::instacne(_pStack);
    createMenuBar();
    configTv();
    configLv();
    readAnaliableDevices();
}


CanMaster::~CanMaster(){
    delete _ui;
    delete [] _pInterface;
    _pDev->disconnectDevice();
    *_pRunGen = 0;
    *_pRunSniff = 0;
}


void CanMaster::readAnaliableDevices() noexcept{
    auto canDevList {QCanBus::instance()->availableDevices(_plugin)};
    for (auto &&s : canDevList){
        _ui->cbInterface->addItem(s.name());
    }
}


void CanMaster::updateUi() noexcept{
    _pTableModel->update();
    _ui->lvData->scrollToBottom();
    _ui->tvData->scrollToBottom();
    _ui->lcdNum1->display(_pStack->size());
}


void CanMaster::configTv() noexcept{
    QTableView *tv = _ui->tvData;

    constexpr int rowHeight {10};
    constexpr int colWidth1 {90};
    constexpr int colWidth2 {50};
    constexpr int colWidth3 {10};
    constexpr int colWidth4 {200};

    tv->setModel(_pTableModel);
    tv->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tv->setFont(QFont("Courier", 10));

    tv->setColumnWidth(0, colWidth1);
    tv->setColumnWidth(1, colWidth2);
    tv->setColumnWidth(2, colWidth3);
    tv->setColumnWidth(3, colWidth4);

    QHeaderView *verticalHeader = tv->verticalHeader();
    verticalHeader->setSectionResizeMode(QHeaderView::Fixed);
    verticalHeader->setDefaultSectionSize(rowHeight);
}


void CanMaster::configLv() noexcept{
    QListView *lv = _ui->lvData;
    
    lv->setModel(_pTableModel);
    lv->setFont(QFont("Courier", 10));
}


void CanMaster::readFrames() noexcept{
    if(_pDev->framesAvailable()){
        auto frameList = _pDev->readAllFrames();
        for (auto frame : frameList) {
            if(_pFilter->checkFrame(frame)){
                _pFilter->saveFrame(frame);
            }
        }
    }

    updateUi();
}


void CanMaster::connectCanDevice() noexcept{
    _pDev->connectDevice();
}


void CanMaster::disconnectCanDevice() noexcept{
    _pDev->disconnectDevice();
}


void CanMaster::createCanDev() noexcept{
    if(!QCanBus::instance()->plugins().contains(QStringLiteral("socketcan")))
            qFatal("Qcab bus doesn't provide the desired plugin \"socketcan\"");

    updateInterfaceName();

    _pDev = QCanBus::instance()->createDevice(
                _plugin,
                _pInterface,
                &_errorString);

    if(!_pDev)
        qDebug() << _errorString;

connect(_pDev, SIGNAL(framesReceived()), this, SLOT(readFrames()));
}


void CanMaster::updateInterfaceName() noexcept{
    if(_ui->cbInterface->currentText() != ""){
        QByteArray ba = _ui->cbInterface->currentText().toLatin1();
        char *data {ba.data()};
        delete[] _pInterface;
        _pInterface = new char[ba.size() + 1];
        for (int i{0}; (_pInterface[i] = *data++) ; i++) {}
    }
    else
        qDebug() << "Empty interface list !";
}


void CanMaster::createMenuBar() noexcept{
    QMenu* menuProject = new QMenu(tr("Project"), this);
    QMenu* menuCan = new QMenu(tr("Can Utils"), this);
    QMenu* menuTools = new QMenu(tr("Tools"), this);
    QMenu* menuHelp = new QMenu(tr("Help"), this);

    _ui->menubar->addMenu(menuProject);
    _ui->menubar->addMenu(menuCan);
    _ui->menubar->addMenu(menuTools);
    _ui->menubar->addMenu(menuHelp);

    menuProject->addAction(tr("new"), this, SLOT(foo()), tr("Ctrl+N"));
    menuProject->addAction(tr("open"), this, SLOT(foo()), tr("Ctrl+O"));
    menuProject->addAction(tr("save"), this, SLOT(foo()), tr("Ctrl+S"));
    menuProject->addAction(tr("save as"), this, SLOT(foo()), tr("Ctrl+Shift+S"));
    menuProject->addAction(tr("exit"), this, SLOT(foo()));

    _pCanGenAction = new QAction(tr("gen"), this);
    _pCanGenAction->setCheckable(true);
    connect(_pCanGenAction, SIGNAL(triggered()), this, SLOT(canGen()));
    menuCan->addAction(_pCanGenAction);

    menuCan->addAction(tr("dump"), this, SLOT(foo()));

    _pCanSniffAction = new QAction(tr("sniff"), this);
    _pCanSniffAction->setCheckable(true);
    menuCan->addAction(_pCanSniffAction);

    menuCan->addAction(tr("player"), this, SLOT(foo()));
    menuCan->addAction(tr("send"), this, SLOT(foo()));

    menuTools->addAction(tr("config"), this, SLOT(foo()));

    menuHelp->addAction(tr("Nobody help you :P"), this, SLOT(foo()));
}


void CanMaster::canGen() noexcept{
    if(*_pRunGen ^= 1){
        _ui->btnGen->setText("Stop simulatiom");

        _params[0] = const_cast<char *>("canGen");
        _params[1] = _pInterface;
        _params[2] = const_cast<char *>("-g");
        _params[3] = const_cast<char *>("500");
        _params[4] = const_cast<char *>("-I");
        _params[5] = const_cast<char *>("001");

        char **ppCanGenArg = _params;
        futureGen = QtConcurrent::run(cu::canGen, 6, ppCanGenArg, _pRunGen);
    }
    else{
        _ui->btnGen->setText("Simulate data");
        futureGen.waitForFinished();
    }
}

void CanMaster::on_btnConnect_clicked(){
    using DevState = QCanBusDevice::CanBusDeviceState;

    if(!_pDev)
        createCanDev();
    if(_pDev->state() == DevState::UnconnectedState){
        createCanDev();
        _ui->btnConnect->setText("Disconnect");
        connectCanDevice();
    }
    else if(_pDev->state() == DevState::ConnectedState){
        _ui->btnConnect->setText("Connect");
        disconnectCanDevice();
    }
}


void CanMaster::on_btnGen_clicked(){
    _pCanGenAction->toggle();
    canGen();
}


void CanMaster::on_btnDump_clicked(){
    _pStack->clearStack();
    _pTableModel->removeRows(0, _pTableModel->rowCount(QModelIndex()));
    _pFilter = FilterDump::instacne(_pStack);
}


void CanMaster::on_btnSniff_clicked(){
    _pStack->clearStack();
    _pTableModel->removeRows(0, _pTableModel->rowCount(QModelIndex()));
    _pFilter = FilterSniff::instance(_pStack);
}


void CanMaster::on_btnRefresh_clicked(){
    readAnaliableDevices();
}
