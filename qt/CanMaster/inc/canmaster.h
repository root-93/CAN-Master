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
        enum {start,stop};

    public:
                                CanMaster(QWidget *parent = nullptr);
                                ~CanMaster();

    public slots:
        void                    foo(){}
        void                    canGen();
        // void                    canSniffer();
        void                    updateUi();

    private:
        Ui::CanMaster           *_ui = nullptr;
        QStringListModel        *_pModel = nullptr;
        TableModel              *_pTableModel = nullptr;
        int                     *_pRunGen = new int;
        int                     *_pRunSniff = new int;
        QAction                 *_pCanGenAction = nullptr;
        QAction                 *_pCanSniffAction = nullptr;
        char                    *_params[3];
        QString                 _errorString;
        QPointer<QCanBusDevice> _pDev = nullptr;

        void                    createMenuBar() noexcept;
        void                    connectCan() noexcept;
        void                    configTv() noexcept;
        void                    configLv() noexcept;
};
#endif // CANMASTER_H
