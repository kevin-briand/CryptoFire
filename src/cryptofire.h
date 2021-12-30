#ifndef CRYPTOFIRE_H
#define CRYPTOFIRE_H

#include <QObject>
#include <QTime>
#include <QDebug>
#include <iostream>
#include <QCryptographicHash>
#include <stdexcept>
#include <QTextCodec>

enum charFormat {
    UTF8,
    UTF16
};

class CryptoFire : public QObject
{
    Q_OBJECT
public:
    enum error { noError, codeSize, sameName, badKey, unknown};
    CryptoFire(int keySize = 50, int codeSize = 4, int charFormat = UTF8, QString key = "");
    bool Add_Encrypted_Key(QString name, QString password, QString key = "");
    bool Remove_Encrypted_Key(QString name);
    QString Get_Key();
    void Test();
    QString Key_To_SHA256(QString name) { QTextCodec *codec = QTextCodec::codecForName("UTF-8");
                                          QByteArray ba = codec->fromUnicode(Get_Encrypted_Key(name));
                                          ba = codec->fromUnicode(Get_Encrypted_Key(name));
        qDebug() << "UTF-8" <<  QCryptographicHash::hash(ba,QCryptographicHash::Sha256).toHex();
                                          return QCryptographicHash::hash(ba,QCryptographicHash::Sha256).toHex(); };

public slots:
    void Decrypt_Data(QString &data, QString name);
    void Encrypt_Data(QString &data, QString name);

signals:
    void Decrypted_Data(QString data);
    void Encrypted_Data(QString data);
    void Encrypted_Data_To_Hexa(QByteArray data);

private:
    QString Get_Encrypted_Key(QString name);
    void Generate_Key(int keySize);
    QString Encrypt_Key(QString password, QString key = nullptr);

    QString _key;
    QStringList _EncryptedKeys;
    const int _codeSize;
    int _charSize;

};

#endif // CRYPTOFIRE_H
