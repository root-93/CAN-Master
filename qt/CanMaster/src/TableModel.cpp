#include "TableModel.hpp"

TableModel::TableModel(QObject *parent) : QAbstractTableModel(parent){}


TableModel::TableModel(const QVector<QCanBusFrame> &frames, QObject *parent) 
    : QAbstractTableModel(parent), frames{frames} {}


int TableModel::rowCount(const QModelIndex &parent) const{
    return parent.isValid() ? 0 : frames.size();
}


int TableModel::columnCount(const QModelIndex &parent)const { 
    return parent.isValid() ? 0 : 4;
}


QVariant TableModel::data(const QModelIndex &index, int role)const {
    static long long mSec;

    if(!index.isValid())
        return QVariant();

    if(index.row() >= frames.size() || index.row() < 0)
        return QVariant();

    if(role == Qt::DisplayRole){
        const auto &frame = frames.at(index.row());

        switch(index.column()){
            case 0:
                mSec = frame.timeStamp().microSeconds();
                return QDateTime::fromMSecsSinceEpoch(mSec).toString("mm:ss:zzz");
            case 1:
                return frame.frameType();
            case 2:
                return toHexString(frame.frameId());
            case 3:
                
                return formatData(frame.payload());
            default:
                break;
        }
    }

    return QVariant();
}



inline QString TableModel::toHexString(const qint32 val)const noexcept{
    return QString("%1").arg(val, 3, 16, QLatin1Char('0')).toUpper();
}


inline QByteArray TableModel::formatData(QByteArray arr)const noexcept{
    arr = arr.toHex().toUpper();
    for (int i = (arr.size() - 2); i>=2 ; i-=2) {
        arr.insert(i, QByteArray(" "));
    }
    return arr;
}


QVariant TableModel::headerData(int section, Qt::Orientation orientation, int role)const {
    if(role != Qt::DisplayRole)
        return QVariant();

    if(orientation == Qt::Horizontal){
        switch (section)
        {
        case 0:
            return tr("TimeStamp");
            break;
        case 1:
        return tr("Type");
            break;
        case 2:
            return tr("ID");
            break;                
        case 3:
            return tr("Data");
            break;
        default:
            break;
        }
    }

    return QVariant();
}


bool TableModel::insertRows(int position, int rows, const QModelIndex &index){
    Q_UNUSED (index);
    beginInsertRows(QModelIndex(), position, position + rows - 1);

    for (int row = 0 ; row < rows ; ++row)
        frames.insert(position, QCanBusFrame());
    
    endInsertRows();
    return true;
}


bool TableModel::removeRows(int position, int rows, const QModelIndex &index){
    Q_UNUSED (index);
    beginRemoveRows(QModelIndex(), position, position + rows - 1);

    for (int row = 0 ; row < rows ; ++row)
        frames.removeAt(position);
    
    endRemoveRows();
    return true;
}


bool TableModel::setData(const QModelIndex &index, const QVariant &value, int role){
    if(index.isValid() && role == Qt::EditRole){
        const int row = index.row();
        auto frame = frames.value(row);
        QCanBusFrame newFrame;

        Q_ASSERT(value.canConvert<QCanBusFrame>());
        newFrame = value.value<QCanBusFrame>();

        switch (index.column())
        {
        case 0:
            frame.setTimeStamp(newFrame.timeStamp());
            break;
        case 1:
            frame.setPayload(newFrame.payload());
            break;
        case 2:
            frame.setFrameId(newFrame.frameId());
            break;
        case 3:
            frame = newFrame;        
            break;
        default:
            return false;
        }

        frames.replace(row, frame);
        emit dataChanged(index, index, {Qt::DisplayRole, Qt::EditRole});

        return true;
    }    

    return false;
}


Qt::ItemFlags TableModel::flags(const QModelIndex &index)const {
    if(!index.isValid())
        return Qt::ItemIsEnabled;
    return QAbstractTableModel::flags(index) | Qt::ItemIsEditable;
}


const QVector<QCanBusFrame>& TableModel::getFrames()const {
    return frames;
}


void TableModel::append(const QCanBusFrame *frame){
    int rowNumber = rowCount(QModelIndex());
    insertRow(rowNumber);
    QVariant v;
    v.setValue(*frame);

    int columns = columnCount(QModelIndex());
    for(int i = 0; i < columns ; i++){
        QModelIndex index = this->index(rowNumber, i, QModelIndex());
        this->setData(index, v);
    }
}


void TableModel::clear(){
    removeRows(0, rowCount(QModelIndex()));
}


