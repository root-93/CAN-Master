#ifndef CANMASTER_H
#define CANMASTER_H

#include <QMainWindow>
#include <QActionGroup>
#include <QStringListModel>

QT_BEGIN_NAMESPACE
namespace Ui { class CanMaster; }
QT_END_NAMESPACE

class CanMaster : public QMainWindow
{
        Q_OBJECT

    public:
        CanMaster(QWidget *parent = nullptr);
        ~CanMaster();

    public slots:
        void foo(){}
        void canGen();

    private:
        Ui::CanMaster *ui;
        QStringListModel *model;
        void createMenuBar() noexcept;


};
#endif // CANMASTER_H
