#include "canmaster.h"
#include "ui_canmaster.h"
#include "CanUtils.hpp"

CanMaster::CanMaster(QWidget *parent): QMainWindow(parent), ui(new Ui::CanMaster){
    ui->setupUi(this);
    createMenuBar();

    model = new QStringListModel(this);
    //some data
    QStringList list {"first", "secoud", "third"};

    model->setStringList(list);

    ui->lvData->setModel(model);
}

CanMaster::~CanMaster(){
    delete ui;
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

    menuCan->addAction(tr("gen"), this, SLOT(canGen()));
    menuCan->actions().back()->setCheckable(true);
    menuCan->addAction(tr("dump"), this, SLOT(foo()));
    menuCan->addAction(tr("sniff"), this, SLOT(foo()));
    menuCan->addAction(tr("player"), this, SLOT(foo()));
    menuCan->addAction(tr("send"), this, SLOT(foo()));

    menuTools->addAction(tr("config"), this, SLOT(foo()));

    menuHelp->addAction(tr("Nobody help you :P"), this, SLOT(foo()), tr("Alt+N"));
}

void CanMaster::canGen(){
    char *param0 = const_cast<char *>("canDump");
    char *param1 = const_cast<char *>("vcan0");
    char *pCanDumpArg[] {param0,
                         param1};

    char **ppCanDumpArg = pCanDumpArg;

    [[maybe_unused]] int returnValue = canutils::canDump(2, ppCanDumpArg);
}
