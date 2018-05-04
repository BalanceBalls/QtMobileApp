#include "pairlistmodel.h"
#include <QDebug>
PairListModel::PairListModel(QObject *parent)
    : QAbstractItemModel(parent)
{
    hash.insert(Qt::UserRole, QByteArray("symbol"));
    hash.insert(Qt::UserRole + 1, QByteArray("price"));
    hash.insert(Qt::UserRole + 2, QByteArray("percent24h"));

}

QModelIndex PairListModel::index(int row, int column, const QModelIndex &parent) const
{

     return createIndex(row,column,parent.row());
}

QModelIndex PairListModel::parent(const QModelIndex &index) const
{
     qDebug() << "parent called ";
    return createIndex(0,1,index.row());
}

int PairListModel::rowCount(const QModelIndex &parent) const
{
    qDebug() << "rowCount called ";
    Q_UNUSED(parent);
    qDebug() << pairList.count();
    return pairList.count();


}

int PairListModel::columnCount(const QModelIndex &parent) const
{
    qDebug() << "column called ";

        return 1;

}

QVariant PairListModel::data(const QModelIndex &index, int role) const
{

    Q_UNUSED(role);

    if (!index.isValid())
        return QVariant();

    if (index.row() >= pairList.size())
          return QVariant();

      PairListItem item = pairList.at(index.row());

      if(role == Qt::UserRole) {
          return item.symobl;
      } else if(role == Qt::UserRole+1)  {
          return item.price;
      } else if(role == Qt::UserRole+2) {
          if( item.percent24h >= 0 ){

          }
          return item.percent24h;
      }

      return QVariant();
}
void PairListModel::readyToDisplay(QList<PairListItem> newList){

    beginResetModel();

    this->pairList = newList;

    qDebug() << "Caught a signal!!!";

    endResetModel();
}
void PairListModel::setPairList(const QList<PairListItem> &value)
{
    this->pairList = value;
}

void PairListModel::addPair(const PairListItem &value)
{
     qDebug() << "appended ";
    this->pairList.append(value);
     foreach (const auto &t , pairList){
         qDebug() << t.price;
     }
}
