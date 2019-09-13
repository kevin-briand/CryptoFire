#ifndef CRYPTOFIRE_H
#define CRYPTOFIRE_H

#include <QObject>
#include <QTime>
#include <QDebug>
#include <iostream>

class CryptoFire : public QObject
{
    Q_OBJECT
public:
    CryptoFire(int keySize = 50, int codeSize = 4, QString key = nullptr);
    bool Add_Encrypted_Key(QString name, QString password);
    bool Remove_Encrypted_Key(QString name);
    QString Get_Key();
    void Test();

public slots:
    void Decrypt_Data(QString &data, QString name);
    void Encrypt_Data(QString &data, QString name);

signals:
    void Decrypted_Data(QString data);
    void Encrypted_Data(QString data);

private:
    void Generate_Key(int keySize);
    QString Encrypt_Key(QString password);

    QString _key;
    QStringList _EncryptedKeys;
    const int _codeSize;

};

#endif // CRYPTOFIRE_H
