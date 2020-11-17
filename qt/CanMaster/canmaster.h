#ifndef CANMASTER_H
#define CANMASTER_H

#include <QMainWindow>
#include <QActionGroup>
#include <QStringListModel>
#include <QPointer>
#include "linux/can.h"
#include <QVector>
#include <QCanBus>

QT_BEGIN_NAMESPACE
namespace Ui { class CanMaster; }
QT_END_NAMESPACE

class CanMaster : public QMainWindow
{
        Q_OBJECT
        struct snif;

    public:
        CanMaster(QWidget *parent = nullptr);
        ~CanMaster();

    public slots:
        void foo(){}
        void canGen();
        void canSniffer();
        void updateUi();

    private slots:
        void on_pushButton_clicked();

    private:
        Ui::CanMaster *ui;
        QStringListModel *model;

        void createMenuBar() noexcept;
        void connectCan() noexcept;

        int *pRunGen = new int;
        int *pRunSniff = new int;
        QPointer<QAction> pCanGenAction = nullptr;
        QPointer<QAction> pCanSniffAction = nullptr;
        char *params[3];
        snif *pSniffBuf = nullptr;
        QString errorString;
        QPointer<QCanBusDevice> pDev = nullptr;

        struct snif {
            int flags;
            long hold;
            long timeout;
            struct timeval laststamp;
            struct timeval currstamp;
            struct can_frame last;
            struct can_frame current;
            struct can_frame marker;
            struct can_frame notch;
        };

};
#endif // CANMASTER_H
