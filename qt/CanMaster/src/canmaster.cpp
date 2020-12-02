#include "../inc/canmaster.h"
#include "ui_canmaster.h"
#include "../inc/CanUtils.hpp"
#include <qdebug.h>
#include <QtConcurrent/qtconcurrentrun.h>
#include <QString>


namespace cu = canutils;

CanMaster::CanMaster(QWidget *parent): QMainWindow(parent), _ui(new Ui::CanMaster){
    _ui->setupUi(this);
    _pTableModel = new TableModel(_pStack->getFrames(), this);
    _pFilter = FilterDump::instacne(_pStack);
    createMenuBar();
    configTv();
    configLv();
    configApp();

    auto canDevList {QCanBus::instance()->availableDevices(plugin)};
    for (auto &&s : canDevList){
        _ui->cbInterface->addItem(s.name());
    }
}


void CanMaster::configApp() noexcept{

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


CanMaster::~CanMaster(){
    delete _ui;
    *_pRunGen = 0;
    *_pRunSniff = 0;
}


void CanMaster::updateUi(){
    while(_pDev->framesAvailable()){
        auto frame = _pDev->readFrame();
        if(_pFilter->checkFrame(frame)){
            //_pFilter->saveFrame(frame);
            _pTableModel->append(&frame);
        }

    }
    _ui->lvData->scrollToBottom();
    _ui->tvData->scrollToBottom();

    _ui->lcdNum1->display(_pStack->size());
}


void CanMaster::connectCan() noexcept{
    _pDev->connectDevice();
}


void CanMaster::createCanDev() noexcept{
    if(!QCanBus::instance()->plugins().contains(QStringLiteral("socketcan")))
            qFatal("Qcab bus doesn't provide the desired plugin \"socketcan\"");

    if(_ui->cbInterface->currentText() != "")
       _interface = _ui->cbInterface->currentText();
    else
        qDebug() << "Empty interface list !";

    _pDev = QCanBus::instance()->createDevice(
                                    plugin,
                                    _interface,
                                    &_errorString);

    if(!_pDev)
        qDebug() << _errorString;

    connect(_pDev, SIGNAL(framesReceived()), this, SLOT(updateUi()));
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
    // connect(_pCanSniffAction, SIGNAL(triggered()), this, SLOT(canSniffer()));
    menuCan->addAction(_pCanSniffAction);

    menuCan->addAction(tr("player"), this, SLOT(foo()));
    menuCan->addAction(tr("send"), this, SLOT(foo()));

    menuTools->addAction(tr("config"), this, SLOT(foo()));

    menuHelp->addAction(tr("Nobody help you :P"), this, SLOT(foo()));
}


void CanMaster::canGen(){
    if(*_pRunGen){
        *_pRunGen = 0;
    }
    else{
        *_pRunGen = 1;

        _params[0] = const_cast<char *>("canGen");
        _params[1] = const_cast<char *>(_interface.toStdString().c_str());

        char **ppCanGenArg = _params;
        QtConcurrent::run(cu::canGen, 2, ppCanGenArg, _pRunGen);
    }
}


void CanMaster::on_btnConnect_clicked(){
    if(!_pDev)
        createCanDev();
    connectCan();
}


void CanMaster::on_btnGen_clicked(){
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
