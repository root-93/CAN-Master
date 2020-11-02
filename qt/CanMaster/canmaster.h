#ifndef CANMASTER_H
#define CANMASTER_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class CanMaster; }
QT_END_NAMESPACE

class CanMaster : public QMainWindow
{
        Q_OBJECT

    public:
        CanMaster(QWidget *parent = nullptr);
        ~CanMaster();

    private:
        Ui::CanMaster *ui;
};
#endif // CANMASTER_H
