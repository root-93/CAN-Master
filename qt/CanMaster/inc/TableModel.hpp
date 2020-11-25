#ifndef TABLEMODEL_H
#define TABLEMODEL_H
#include <QAbstractTableModel>
#include <QCanBus>
#include <QDateTime>
#include "../inc/Qt_global.h"


class TableModel : public QAbstractTableModel{
        Q_OBJECT
    public:
                        TableModel(QObject *patern = nullptr);
                        TableModel(const QVector<QCanBusFrame> &frames, QObject *parent = nullptr);

        int             rowCount(const QModelIndex &parent) const override;
        int             columnCount(const QModelIndex &parent)const override;
        QVariant        data(const QModelIndex &index, int role)const override;
        QVariant        headerData(int section, Qt::Orientation orientation, int role)const override;
        Qt::ItemFlags   flags(const QModelIndex &index)const override;
        bool            setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
        bool            insertRows(int position, int rows, const QModelIndex &index = QModelIndex()) override;
        bool            removeRows(int position, int rows, const QModelIndex &index = QModelIndex()) override;
        void            append(const QCanBusFrame *frame) noexcept;
        void            clear() noexcept;
        const QVector<QCanBusFrame>& getFrames() const;

    private:
        QVector<QCanBusFrame> frames;
        QString         toHexString(qint32 val)const noexcept;
        QByteArray      formatData(QByteArray arr)const noexcept;
        

};

#endif // TABLEMODEL_H
