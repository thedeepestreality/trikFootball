#ifndef TEST_H
#define TEST_H

#include <trikControl/brickFactory.h>
#include <trikControl/brickInterface.h>
#include <trikKernel/configurer.h>

#include <QObject>
#include <QTimer>
#include <QWidget>

#include <QStringList>
#include <QHostAddress>
#include <QFile>
#include <QTimer>
#include <QTextStream>
#include <QtCore/qmath.h>

#include <QUdpSocket>
#include <QNetworkInterface>
#include <QList>

#include <trikControl/brickFactory.h>
#include <trikControl/brickInterface.h>
#include <trikKernel/loggingHelper.h>

using namespace trikControl;

#define KICKER 45

class Test : public QObject
{
    Q_OBJECT
    public:
        explicit Test(QThread *guiThread);
        ~Test();
    private:
    //Brick brick;
        BrickInterface * brick;

        bool state;
//    QTcpServer * server;
//    QTcpSocket * client;
        QUdpSocket *socket;
        QUdpSocket *addrSocket;
        QUdpSocket *broadcastSocket;

        QTextStream * txt;
        QFile *file;
        QTimer *mrTimer;
        QString mac;

        int num;


    private slots:
        void readDatagram();
        void stopMotors();

        void kickerBack();
    //    void action();
    //    void acceptConnection();
    //    void serveConnection();
    //    void getData();
    //    void stop();
};


#endif // TEST_H
