#include "json_loader.h"
#include <QUrlQuery>
#include <QNetworkReply>
#include <QUrl>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QString>
#include <QStringList>

json_loader::json_loader(QObject *parent) : QObject(parent)
{
        networkManager = new QNetworkAccessManager();

        connect(networkManager, &QNetworkAccessManager::finished, this, &json_loader::onValuesObtained);

        networkManager->get(QNetworkRequest(QUrl("https://api.coinmarketcap.com/v1/ticker/?limit=50")));//https://api.coinmarketcap.com/v1/ticker/?limit=10
}
void json_loader::requestPricesFromApi(){

    qDebug("called API data loader method");

}

void json_loader::onValuesObtained(QNetworkReply *reply){


    if(reply->error() == QNetworkReply::NoError){

  qDebug("called API data loader method");

        QString strReply = (QString)reply->readAll();
        QJsonDocument doc = QJsonDocument::fromJson(strReply.toUtf8());
        QJsonArray coincapArray = doc.array();

        for (int i = 0; i < coincapArray.size(); i++ ){

           QJsonObject obj = coincapArray.at(i).toObject();

           PairListItem tempItem;
             tempItem.symobl =     obj.value("symbol").toString();
             tempItem.price =      obj.value("price_usd").toString().toDouble();
             tempItem.percent24h = obj.value("percent_change_24h").toString().toDouble();

           pairs.append(tempItem);

        }

        emit listIsReady(pairs);

    }else{
        qDebug() << reply->error();
        qDebug() << QSslSocket::sslLibraryBuildVersionString();
        qDebug() << QSslSocket::supportsSsl();

    }
//    foreach (const auto &t , pairs){
//        qDebug() << t.price;
//    }
}

QList<PairListItem> json_loader::getPairs() const
{
    qDebug() << " get pairs is called";
    foreach (const auto &t , pairs){
        qDebug() << t.price;
    }
    return pairs;
}
