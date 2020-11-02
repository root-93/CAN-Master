#include "canmaster.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CanMaster w;
    w.show();
    return a.exec();
}
