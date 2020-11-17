#ifndef CANMASTER_H
#define CANMASTER_H

#include <QMainWindow>
#include <QActionGroup>
#include <QStringListModel>
#include <QPointer>
#include <QVector>
#include <QCanBus>
#include <QTableView>
#include <QListView>
#include "TableModel.hpp"
#include "linux/can.h"

QT_BEGIN_NAMESPACE
namespace Ui { class CanMaster; }
QT_END_NAMESPACE

class CanMaster : public QMainWindow
{
        Q_OBJECT
        struct snif;
        enum {start,stop};

    public:
        CanMaster(QWidget *parent = nullptr);
        ~CanMaster();

    public slots:
        void foo(){}
        void canGen();
        void canSniffer();
        void updateUi();

    private:
        Ui::CanMaster *ui = nullptr;
        QStringListModel *model = nullptr;
        TableModel *tableModel = nullptr;
        int* pRunGen = new int;
        int* pRunSniff = new int;
        QAction *pCanGenAction = nullptr;
        QAction *pCanSniffAction = nullptr;
        char *params[3];
        snif *pSniffBuf = nullptr;
        QString errorString;
        QPointer<QCanBusDevice> pDev = nullptr;

        void createMenuBar() noexcept;
        void connectCan() noexcept;
        void configTv(QTableView *tv) noexcept;
        void configLv(QListView *lv) noexcept;
};
#endif // CANMASTER_H
