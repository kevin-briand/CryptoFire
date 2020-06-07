#include <QCoreApplication>
#include <cryptofire.h>
#include <iostream>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    //test
    CryptoFire *crypto = new CryptoFire(50,4,UTF16);
    crypto->Test();

}
