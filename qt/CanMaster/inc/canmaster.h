#ifndef CANMASTER_H
#define CANMASTER_H

#include <QMainWindow>
#include <QActionGroup>
#include <QStringListModel>
#include <QPointer>
#include <QVector>
#include <QCanBus>
#include <QFuture>
#include <QTableView>
#include <QListView>
#include <QTimer>
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
                                explicit CanMaster(QWidget *parent = nullptr);
                                ~CanMaster();

    private slots:
        void                    foo(){}
        void                    canGen() noexcept;
        void                    readFrames() noexcept;
        void                    on_btnConnect_clicked();
        void                    on_btnGen_clicked();
        void                    on_btnDump_clicked();       
        void                    on_btnSniff_clicked();
        void                    on_btnRefresh_clicked();

    private:
        Ui::CanMaster           *_ui {};
        QStringListModel        *_pModel {};
        TableModel              *_pTableModel {};
        int                     *_pRunGen {new int(0)};
        int                     *_pRunSniff {new int(0)};
        QAction                 *_pCanGenAction {};
        QAction                 *_pCanSniffAction {};
        char                    *_params[6]{};
        QString                 _errorString;
        QPointer<QCanBusDevice> _pDev {};
        const QString           _plugin {"socketcan"};
        char                    *_pInterface{new char[6]{'v','c','a','n','0',0}};
        Filter                  *_pFilter {};
        Stack                   *_pStack {new Stack()};
        QFuture<void>           futureGen;
        QTimer                  *timer = new QTimer(this);

        void                    createMenuBar() noexcept;
        void                    createCanDev() noexcept;
        void                    disconnectCanDevice() noexcept;
        void                    connectCanDevice() noexcept;
        void                    configTv() noexcept;
        void                    configLv() noexcept;
        void                    updateUi() noexcept;
        void                    readAnaliableDevices() noexcept;
        void                    updateInterfaceName() noexcept;
};
#endif // CANMASTER_H
