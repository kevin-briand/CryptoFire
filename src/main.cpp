#include <QCoreApplication>
#include <cryptofire.h>
#include <iostream>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    //test
    std::cout << "STARTING TEST UTF-8\n\n";
    CryptoFire *crypto = new CryptoFire();
    crypto->Test();
    std::cout << "\n\nSTARTING TEST UTF-16\n\n";
    crypto = new CryptoFire(50,4,UTF16);
    crypto->Test();

}
