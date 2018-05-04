#ifndef CLIENTFORSERVER_H
#define CLIENTFORSERVER_H

#include <QObject>
#include <QTcpSocket>
#include <serverdatamodel.h>
class ClientForServer : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString serverText READ getText WRITE setText NOTIFY textChanged)
public:
    explicit ClientForServer(QObject *parent = nullptr);

signals:
    void textChanged(QString);
    void listParsed(QList<ServerDataItem> list);
public slots:
    void connectToServer();
    void setText(QString text);
    QString getText() const;
private slots:
    void readTcpData();

private:
    QTcpSocket * _pSocket;
    void parseList(QString data);
    QString serverText;
};

#endif // CLIENTFORSERVER_H
