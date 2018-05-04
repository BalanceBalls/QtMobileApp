#ifndef JSON_LOADER_H
#define JSON_LOADER_H
#include <QNetworkAccessManager>
#include <QObject>
#include <pairlistmodel.h>
class json_loader : public QObject
{
    Q_OBJECT

public:
    explicit json_loader(QObject *parent = nullptr);

   QList<PairListItem> getPairs() const;

signals:

    void listIsReady(const QList<PairListItem>);

public slots:
    void requestPricesFromApi();

private slots:
    void onValuesObtained(QNetworkReply *reply);

private:
        QNetworkAccessManager *networkManager;
        QList<PairListItem> pairs;

};

#endif // JSON_LOADER_H
