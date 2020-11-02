#include "canmaster.h"
#include "ui_canmaster.h"

CanMaster::CanMaster(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::CanMaster)
{
    ui->setupUi(this);
}

CanMaster::~CanMaster()
{
    delete ui;
}

