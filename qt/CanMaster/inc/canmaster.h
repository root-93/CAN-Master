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
#include "FilterDump.hpp"
#include "FilterSniff.hpp"
#include "Stack.hpp"


QT_BEGIN_NAMESPACE
namespace Ui { class CanMaster; }
QT_END_NAMESPACE

class CanMaster : public QMainWindow
{
        Q_OBJECT
        enum {start,stop};

    public:
                                CanMaster(QWidget *parent = nullptr);
                                ~CanMaster();

    private slots:
        void                    foo(){}
        void                    canGen();
        void                    updateUi();
        void                    on_btnConnect_clicked();
        void                    on_btnGen_clicked();
        void                    on_btnDump_clicked();       
        void                    on_btnSniff_clicked();

    private:
        Ui::CanMaster           *_ui {};
        QStringListModel        *_pModel {};
        TableModel              *_pTableModel {};
        int                     *_pRunGen {new int};
        int                     *_pRunSniff {new int};
        QAction                 *_pCanGenAction {};
        QAction                 *_pCanSniffAction {};
        char                    *_params[3];
        QString                 _errorString;
        QPointer<QCanBusDevice> _pDev {};
        const QString           plugin {"socketcan"};
        QString                 _interface {"vcan0"};
        Filter                  *_pFilter {};
        Stack                   *_pStack {new Stack()};

        void                    createMenuBar() noexcept;
        void                    createCanDev() noexcept;
        void                    connectCan() noexcept;
        void                    configTv() noexcept;
        void                    configLv() noexcept;
        void                    configApp() noexcept;
};
#endif // CANMASTER_H
