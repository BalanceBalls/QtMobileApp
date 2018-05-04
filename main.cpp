#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "json_loader.h"
#include <pairlistmodel.h>
#include <clientforserver.h>
#include <serverdatamodel.h>
int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    QQmlContext* context = engine.rootContext();

    json_loader loader;

    ClientForServer client;
    context->setContextProperty("clientInstance", &client);


    PairListModel *myModel = new PairListModel() ;
    ServerDataModel *serverModel =  new ServerDataModel();
//    myModel->addPair(PairListItem("BTC", 1443, 0.43));
//    myModel->addPair(PairListItem("LTC", 141233, 0.43));
//    myModel->addPair(PairListItem("ETC", 1443, 0.13));
//    myModel->addPair(PairListItem("FTC", 13, -0.43));

    myModel->setPairList( loader.getPairs() );
    //serverModel->setPairListSer();
    context->setContextProperty("coin", myModel);
    context->setContextProperty("serverDataModel", serverModel);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));


    if (engine.rootObjects().isEmpty())
        return -1;


QObject::connect(&loader, SIGNAL(listIsReady(QList<PairListItem>)),
                 myModel, SLOT(readyToDisplay(QList<PairListItem>)));
QObject::connect(&client, SIGNAL(listParsed(QList<ServerDataItem>)),
                 serverModel, SLOT(readyToDisplaySer(QList<ServerDataItem>)));
    return app.exec();
}
