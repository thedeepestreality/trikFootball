#include <QtGui/QApplication>
#include <QMetaType>
#include <test.h>


int main(int argc, char *argv[])
{

   // qRegisterMetaType<QPair<float,float>>("QPair<float,float>");
    QApplication a(argc, argv);
    Test test(a.thread());

    return a.exec();
}
