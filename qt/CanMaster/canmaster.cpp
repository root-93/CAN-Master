#include "canmaster.h"
#include "ui_canmaster.h"

CanMaster::CanMaster(QWidget *parent): QMainWindow(parent), ui(new Ui::CanMaster){
    ui->setupUi(this);




    
}

CanMaster::~CanMaster(){
    delete ui;
}

void CanMaster::createMenuBar(){
    QMenu* menuProject = new QMenu(tr("Project"), this);
    QMenu* menuCan = new QMenu(tr("Can Utils"), this);
    QMenu* menuTools = new QMenu(tr("Tools"), this);
    QMenu* menuHelp = new QMenu(tr("Help"), this);
    
    ui->menubar->addMenu(menuProject);
    ui->menubar->addMenu(menuCan);
    ui->menubar->addMenu(menuTools);
    ui->menubar->addMenu(menuHelp);

    menuProject->addAction(tr("new"), this, SLOT(foo()), tr("Alt+B"));
    menuProject->addAction(tr("open"), this, SLOT(foo()), tr("Alt+N"));
    menuProject->addAction(tr("save"), this, SLOT(foo()), tr("Alt+N"));
    menuProject->addAction(tr("save as"), this, SLOT(foo()), tr("Alt+N"));
    menuProject->addAction(tr("exit"), this, SLOT(foo()), tr("Alt+N"));

    menuCan->addAction(tr("gen"), this, SLOT(foo()), tr("Alt+N"));
    menuCan->addAction(tr("dump"), this, SLOT(foo()), tr("Alt+N"));
    menuCan->addAction(tr("sniff"), this, SLOT(foo()), tr("Alt+N"));
    menuCan->addAction(tr("player"), this, SLOT(foo()), tr("Alt+N"));
    menuCan->addAction(tr("send"), this, SLOT(foo()), tr("Alt+N"));

    menuHelp->addAction(tr("Nobody help you :P"), this, SLOT(foo()), tr("Alt+N"));

}
