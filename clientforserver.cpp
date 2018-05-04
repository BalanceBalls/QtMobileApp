#include "clientforserver.h"
#include <QDebug>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
ClientForServer::ClientForServer(QObject *parent) : QObject(parent)
{

}
void ClientForServer::connectToServer(){
    qDebug() << "Starting connection...";
    QByteArray data;
    data = "\n hello from the App \n";
       _pSocket = new QTcpSocket( this );
       connect( _pSocket, SIGNAL(readyRead()), SLOT(readTcpData()) );

       _pSocket->connectToHost("localhost", 1234);
       if( _pSocket->waitForConnected() ) {
           _pSocket->write( data );
       }
}

void ClientForServer::readTcpData(){
    QString receivedData = _pSocket->readAll();
   // qDebug() << receivedData;
   // this->setText(receivedData);
   parseList(receivedData);
}
void ClientForServer::parseList(QString data){
 QList<ServerDataItem> compList;
 QJsonDocument doc = QJsonDocument::fromJson(data.toUtf8());
 QJsonObject obj=  doc.object();
 QJsonArray arr = obj.value("ID").toArray();
 for (int i = 0; i < arr.size(); i++){
    QJsonObject tempObj = arr.at(i).toObject();

    ServerDataItem tempItem;
        tempItem.model_date = tempObj.value("model_date").toString();
        tempItem.Type = tempObj.value("Type").toString();
        tempItem.Market = tempObj.value("Market").toString();
        tempItem.Pos = tempObj.value("Pos").toString().toInt();
        tempItem.Bid = tempObj.value("Bid").toString().toDouble();
        tempItem.Cur_rate = tempObj.value("Cur_rate").toString().toDouble();
        tempItem.Total = tempObj.value("Total").toString().toDouble();
        qDebug() << tempObj.value("Market").toString();
        qDebug() << tempObj.value("model_date").toString();
    compList.append(tempItem);
 }

 emit listParsed(compList);

}
QString ClientForServer::getText() const
{
    return serverText;
}

void ClientForServer::setText(QString text)
{
    if (text != serverText)
    {
        serverText = text;
        emit textChanged(text);
        _pSocket->close();
    }
}
