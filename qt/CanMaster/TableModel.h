#ifndef TABLEMODEL_H
#define TABLEMODEL_H
#include <QAbstractTableModel>

struct canFrame{
        int id;
};

class TableModel : public QAbstractItemModel{
        Q_OBJECT
    public:
        TableModel(QObject *patern = nullptr);
        TableModel(QVector<canFrame> &frames, QObject *parent = nullptr);

        int rowCount(const QModelIndex &parent) const override;
        int columnCount(const QModelIndex &parent)const override;
        QVariant data(const QModelIndex &index, int role)const override;
        QVariant headerData(int section, Qt::Orientation orientation, int role)const override;
        Qt::ItemFlags flags(const QModelIndex &index)const override;
        bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
        bool insertRows(int position, int rows, const QModelIndex &index = QModelIndex()) override;
        bool removeRows(int position, int rows, const QModelIndex &index = QModelIndex()) override;
        const QVector<canFrame> &getFrames() const;

    private:
        QVector<canFrame> frames;
};

#endif // TABLEMODEL_H
