#ifndef SERVERDATAMODEL_H
#define SERVERDATAMODEL_H

#include <QAbstractItemModel>
#include <QObject>

struct ServerDataItem{
  QString model_date;
  QString Type;
  QString Market;
  int Pos;
  double Bid;
  double Cur_rate;
  double Total;

  ServerDataItem(QString m_date , QString m_type, QString m_market,
               int m_pos, double m_bid , double m_cur_rate, double m_total){
      this->model_date = m_date;
      this->Type = m_type;
      this->Market = m_market;
      this->Pos = m_pos;
      this->Bid = m_bid;
      this->Cur_rate = m_cur_rate;
      this->Total = m_total;
  }
  ServerDataItem(){

  }
};

class ServerDataModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    explicit ServerDataModel(QObject *parent = nullptr);

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    QModelIndex index(int row, int column,
                      const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &index) const override;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role) const override;

    QHash<int, QByteArray> roleNames() const {return hash;}
    void setPairListSer(const QList<ServerDataItem> &value);
    QList<ServerDataItem> serverList;
private:
  QHash<int, QByteArray> hash;
public slots:
    void readyToDisplaySer(QList<ServerDataItem> completeList);
signals:
    void triggerDisplaySer(bool doDisplay);

};

#endif // SERVERDATAMODEL_H
