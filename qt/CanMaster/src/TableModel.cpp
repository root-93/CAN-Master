#include "../inc/TableModel.hpp"

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
    if(!index.isValid())
        return QVariant();

    if(index.row() >= frames.size() || index.row() < 0)
        return QVariant();

    if(role == Qt::DisplayRole){
        const auto &frame = frames.at(index.row());

        switch(index.column()){
            case 0:
                return frame.timeStamp().microSeconds();
            case 1:
                return frame.payload().toHex();
            case 2:
                return frame.frameId();
            case 3:
                return frame.toString();
            default:
                break;
        }
    }

    return QVariant();
}


QVariant TableModel::headerData(int section, Qt::Orientation orientation, int role)const {
    if(role != Qt::DisplayRole)
        return QVariant();

    if(orientation == Qt::Horizontal){
        switch (section)
        {
        case 0:
            return tr("timeStamp");
            break;
        case 1:
        return tr("payload");
            break;
        case 2:
            return tr("ID");
            break;                
        case 3:
            return tr("frame");
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

bool TableModel::append(const QCanBusFrame *frame){
    int rowNumber = rowCount(QModelIndex());
    insertRow(rowNumber);
    QVariant v;
    v.setValue(*frame);

    for(int i = 0, columns = columnCount(QModelIndex()) ; i < columns ; i++){
        QModelIndex index = this->index(rowNumber, i, QModelIndex());
        this->setData(index, v, Qt::EditRole);
    }

    return true;
}
