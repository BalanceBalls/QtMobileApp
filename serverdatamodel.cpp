#include "serverdatamodel.h"
#include <QDebug>
ServerDataModel::ServerDataModel(QObject *parent)
    : QAbstractItemModel(parent)
{
    hash.insert(Qt::UserRole, QByteArray("model_date"));
    hash.insert(Qt::UserRole + 1, QByteArray("Type"));
    hash.insert(Qt::UserRole + 2, QByteArray("Market"));
    hash.insert(Qt::UserRole + 3, QByteArray("Pos"));
    hash.insert(Qt::UserRole + 4, QByteArray("Bid"));
    hash.insert(Qt::UserRole + 5, QByteArray("Cur_rate"));
    hash.insert(Qt::UserRole + 6, QByteArray("Total"));
}

QVariant ServerDataModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    // FIXME: Implement me!
}

QModelIndex ServerDataModel::index(int row, int column, const QModelIndex &parent) const
{
     return createIndex(row,column,parent.row());
}

QModelIndex ServerDataModel::parent(const QModelIndex &index) const
{
     return createIndex(0,1,index.row());
}

int ServerDataModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    qDebug() << serverList.count();
    return serverList.count();
}

int ServerDataModel::columnCount(const QModelIndex &parent) const
{
    return 1;

}

QVariant ServerDataModel::data(const QModelIndex &index, int role) const
{
    Q_UNUSED(role);

    if (!index.isValid())
        return QVariant();

    if (index.row() >= serverList.size())
          return QVariant();

      ServerDataItem item = serverList.at(index.row());

      if(role == Qt::UserRole) {
          return item.model_date;
      } else if(role == Qt::UserRole+1)  {
          return item.Type;
      } else if(role == Qt::UserRole+2) {
          return item.Market;
      }else if(role == Qt::UserRole + 3){
         return item.Pos;
      }else if(role == Qt::UserRole + 4){
         return item.Bid;
      }else if(role == Qt::UserRole + 5){
         return item.Cur_rate;
      }else if(role == Qt::UserRole + 6){
        return item.Total;
      }


      return QVariant();
}
void ServerDataModel::setPairListSer(const QList<ServerDataItem> &value)
{
    this->serverList = value;
}
void ServerDataModel::readyToDisplaySer(QList<ServerDataItem> newList){

    beginResetModel();

    this->serverList = newList;

    qDebug() << "Caught a signal for server list!";

    endResetModel();
}
