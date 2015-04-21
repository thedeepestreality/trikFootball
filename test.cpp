#include "test.h"

Test::Test(QThread *guiThread)//:
    //brick(*guiThread,"/home/root/arm-release/")
{

   // brick = BrickFactory::create(*guiThread, "./system-config.xml", "./selftest-model-config.xml", "./");
    brick = BrickFactory::create(*guiThread, "./system-config.xml", "./selftest-model-config.xml", "./");
    //BrickFactory::create()
    qDebug()<<"Started!";
    //brick->motor("M1")->setPower(80);

    socket = new QUdpSocket(this);
    connect(socket,SIGNAL(readyRead()),this,SLOT(readDatagram()));
    if (socket->bind(QHostAddress::Any,3001))
        qDebug()<<"Socket bind!";
    else
        qDebug()<<"Socket error!";

    num = -1;
    mac= "";

    QList<QNetworkInterface> ntw_lst = QNetworkInterface::allInterfaces();
    for (int i=0;i<ntw_lst.size();++i)
    {
        qDebug()<<ntw_lst[i].humanReadableName();
        if (!ntw_lst[i].humanReadableName().compare("wlan0"))
        {
            mac = ntw_lst[i].hardwareAddress();
            qDebug() << "\t" << mac;
        }
    }

//    QTimer::singleShot(2000,this,SLOT(stopMotors()));
//    brick->motor("M1")->setPower(60);
//    brick->motor("M2")->setPower(60);
//    qDebug()<<"motors started!";
    //QNetworkInterface::;
    //socket->bind()


}

void Test::stopMotors()
{
    brick->motor("M1")->setPower(0);
    brick->motor("M2")->setPower(0);
    qDebug()<<"Motors stopped!";
}

void Test::readDatagram()
{
    QByteArray datagram;
//    qDebug()<<"Datagram!!";
//    datagram.resize(socket->pendingDatagramSize());
    QHostAddress *addr = new QHostAddress();
//    socket->readDatagram(datagram.data(),datagram.size(),addr);
//    qDebug()<<"from: "<<addr->toString();
//    qDebug()<<"data:"<<datagram;

//    QString str(datagram);
//    qDebug()<<"Str: "<<str;
//    QStringList lst = str.split(" ");
//    qDebug()<<lst.size()<<lst[0];

//    if (!lst[0].compare("req"))
//    {
//        socket->writeDatagram((QString("mac ")+mac).toUtf8(),*addr,3000);
//    }

    while (socket->hasPendingDatagrams())
    {
        //QHostAddress *addr;
        datagram.resize(socket->pendingDatagramSize());
        socket->readDatagram(datagram.data(),datagram.size(),addr);
        QString str(datagram);
        QStringList lst = str.split(' ');

        qDebug()<<"Datagram from "<<addr->toString()<<": "<<str;

        if (!lst[0].compare("req"))
        {
            socket->writeDatagram((QString("mac ")+mac).toUtf8(),*addr,3000);
        }
//        if (!lst[0].compare("num"))
//        {
//            num = lst[1].toInt();
//        }
        else if (!lst[0].compare("rule"))
        {
            int right=0;
            int l = 0;
            if (datagram[5]>100) l=datagram[5]-256; else l=datagram[5];
            if (datagram[6]>100) right=datagram[6]-256; else right=datagram[6];
            qDebug()<<l<<" "<<right;
            brick->motor("M1")->setPower(l);
            brick->motor("M2")->setPower(right);
        }

    }
}

//void Test::action(){

//    brick.motor("JM1")->powerOff();
//}

//void Test::acceptConnection()
//{
//    qDebug() << "New connection!";
//    client=server->nextPendingConnection();
//    connect(client,SIGNAL(readyRead()),this,SLOT(serveConnection()));
//   // connect(client,SIGNAL(disconnected()),this,SLOT(closeConnection()));
//}

//void Test::getData()
//{
//    float enc_l = brick.encoder("JB4")->read();
//    float enc_r = -brick.encoder("JB3")->read();


//    vl=enc_l-vl;
//    vr=enc_r-vr;

//    double v = (vl+vr)*0.6872;

//    vl = enc_l;
//    vr = enc_r;

//     QVector<int> temp;
//     temp = brick.gyroscope()->read();
//     double w = (double)(temp[2]+38)/820.846931;

//     double uv = -1.2504*v + 62.4875;
//     double uw = -8.2418*w + 13.7363;
//     //brick.motor("JM3")->setPower(-(uv-0.5*uw));
//    // brick.motor("M1")->setPower((uv+0.5*uw));

//     //double u = -60*w+a*xd/b-60*xd-18;
//     //brick.motor("JM3")->setPower(-40);
//    // brick.motor("M1")->setPower(qCeil(u));

//     QString resp=QString::number(enc_l)+QString(" ")+QString::number(enc_r)+QString(" ")+QString::number(w)+QString(" ")+QString::number(temp[2])+QString("\n");
//    // client->write(resp.toStdString().c_str(),resp.size());
//    if (client->state()==QTcpSocket::ConnectedState)
//    {
//        client->write(resp.toAscii());
//    }
//    //    QVector<int> temp;
////    temp = brick.gyroscope()->read();
////    (*txt)<<temp[2]<<QString("\n");

//   // qDebug()<<encoder->read();
//  //  qDebug()<<brick.encoder("JB4")->read();
//}

//void Test::stop()
//{

//   // mrTimer->stop();
//  //  file->close();

//   // brick.motor("JM1")->powerOff();
//   // brick.motor("JM2")->powerOff();
//    mrTimer->stop();
//    client->close();
//    brick.motor("JM3")->powerOff();
//    brick.motor("M1")->powerOff();
//   // qDebug()<<brick.encoder("JB3")->read();
//  //  qDebug()<<brick.encoder("JB4")->read();
//   // printf("encoders: %d %d\n",brick.encoder("JB1")->read(),brick.encoder("JB2")->read());
//}

//void Test::serveConnection()
//{

//    qDebug()<<"Received!";
//   QString str=client->readLine();
//   qDebug()<<str;
//   //QByteArray data = client->readAll();
//   QStringList list = str.split(" ");
//   if (list.size()==2)
//   {//
//      // brick.motor()
//        int l =list[0].toInt();
//        int r =list[1].toInt();
//        if (l==0 && r==0)
//        {
//            brick.motor("JM3")->powerOff();
//            brick.motor("M1")->powerOff();
//        }
//        else
//        {

//           brick.motor("JM3")->setPower(l);
//           brick.motor("M1")->setPower(r);

//        }
//       // mrTimer->start(50);

//   }
//   else if (!str.compare("0"))
//   {
//       brick.encoder("JB4")->reset();
//       brick.encoder("JB3")->reset();
//       mrTimer->start(50);
//       QTimer::singleShot(3000,this,SLOT(stop()));
//   }

//  // QVector<int> temp;
// //  temp = brick.gyroscope()->read();
//  // brick.gyroscope()->read();

//   //gyroOriginalTilts[0] += temp[0];
//  // gyroOriginalTilts[1] += temp[1];
//   //gyroOriginalTilts[2] += temp[2];

// //  QString resp=QString::number(temp[0])+" "+QString::number(temp[1])+" "+QString::number(temp[2]);

//   //QByteArray data()
//  // client->write(resp.toStdString().c_str(),resp.size());

//}

Test::~Test()
{
//    brick.motor("JM1")->powerOff();
//    brick.motor("JM2")->powerOff();
}
