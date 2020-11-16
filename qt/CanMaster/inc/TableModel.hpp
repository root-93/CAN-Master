#ifndef TABLEMODEL_H
#define TABLEMODEL_H
#include <QAbstractTableModel>
#include <QCanBus>
#include "../inc/Qt_global.h"

// struct CanFrame{
//         // adding new member update columnCount func
//         int id;

//         bool operator==(const CanFrame &other) const noexcept{
//             return id == other.id;
//         }
// };

class TableModel : public QAbstractTableModel{
        Q_OBJECT
    public:
        TableModel(QObject *patern = nullptr);
        TableModel(const QVector<QCanBusFrame> &frames, QObject *parent = nullptr);

        int rowCount(const QModelIndex &parent) const override;
        int columnCount(const QModelIndex &parent)const override;
        QVariant data(const QModelIndex &index, int role)const override;
        QVariant headerData(int section, Qt::Orientation orientation, int role)const override;
        Qt::ItemFlags flags(const QModelIndex &index)const override;
        bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
        bool insertRows(int position, int rows, const QModelIndex &index = QModelIndex()) override;
        bool removeRows(int position, int rows, const QModelIndex &index = QModelIndex()) override;
        bool append(const QCanBusFrame *frame);
        const QVector<QCanBusFrame>& getFrames() const;

    private:
        QVector<QCanBusFrame> frames;
};

#endif // TABLEMODEL_H