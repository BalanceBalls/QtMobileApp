#ifndef PAIRLISTMODEL_H
#define PAIRLISTMODEL_H

#include <QAbstractItemModel>
#include <QObject>

struct PairListItem{
  QString symobl;
  double price;
  double percent24h;

  PairListItem(QString s , double p , double c){
      this->symobl = s;
      this->price = p;
      this->percent24h = c;
  }
  PairListItem(){

  }
};

class PairListModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    explicit PairListModel(QObject *parent = 0);


    // Basic functionality:
    QModelIndex index(int row, int column,
                      const QModelIndex &parent = QModelIndex()) const override;

    QModelIndex parent(const QModelIndex &index) const override;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role) const override;

    QHash<int, QByteArray> roleNames() const {return hash;}
//    bool setData(const QModelIndex &index, const QVariant &value,
//                    int role = Qt::EditRole);
    QList<PairListItem> pairList;

    void setPairList(const QList<PairListItem> &value);
    void addPair(const PairListItem &value);
private:
    QHash<int, QByteArray> hash;
   // json_loader loader;
public slots:
    void readyToDisplay(QList<PairListItem> newList);
//private slots:
//    void displayList(bool setView);
signals:
    void triggerDisplay(bool doDisplay);
};

#endif // PAIRLISTMODEL_H
