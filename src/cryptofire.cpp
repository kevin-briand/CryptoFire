#include "cryptofire.h"

//keySize : Défini la taille de la clé de cryptage
//codeSize : défini la difficulté du cryptage basé sur le mot de passe, celui-ci doit être au minimum de la taille du codeSize
CryptoFire::CryptoFire(int keySize, int codeSize, int charFormat, QString key):
    _codeSize(codeSize)
{
    srand(time(0));

    if(codeSize <= 0) {
        qDebug() << "error : bad codeSize";
        return;
    }

    qDebug() << "Test hash : " << QCryptographicHash::hash("zefjio('zefjioézarfdgkçtrgej",QCryptographicHash::Sha256).toHex();

    _charSize = charFormat == UTF16 ? 43000 : 250;

    if(key.isEmpty()) {
        Generate_Key(keySize);
    }
    else {
        _key = key;
    }
}

QString CryptoFire::Get_Key()
{
    return _key;
}

void CryptoFire::Test()
{
    std::cout << "Start Test\n";
    std::cout << "Valid test key : " << Add_Encrypted_Key("test","Passwdhuihliuhzefz6") << "\n";

    std::cout << "fail test same name : " << Add_Encrypted_Key("test","Test2") << "\n";
    std::cout << "fail test password too short : " << Add_Encrypted_Key("test2","pas") << "\n";
    std::cout << "Valid test key test2 : " << Add_Encrypted_Key("test2","rgreghulihulilh156regregregfze") << "\n\n";

    std::cout << "Test encryption : \n";
    std::cout << "Text 'Ceci est un test' : \n\n";
    std::cout << "Test 1(test) : \n";
    QString test = "Ceci est un test";
    Encrypt_Data(test, "test");
    std::cout << "Encrypted : ";
    std::cout << test.toStdString() << "\n";
    std::cout << "Decrypted : ";
    Decrypt_Data(test, "test");
    std::cout << test.toStdString() << "\n\n";

    std::cout << "Test 2(test2) : \n";
    Encrypt_Data(test, "test2");
    std::cout << "Encrypted : ";
    std::cout << test.toStdString() << "\n";
    std::cout << "Decrypted : ";
    Decrypt_Data(test, "test2");
    std::cout << test.toStdString() << "\n\n";

    std::cout << "Test 3(E=test, D=test2) : \n";
    Encrypt_Data(test, "test");
    std::cout << "Encrypted : ";
    std::cout << test.toStdString() << "\n";
    std::cout << "Decrypted : ";
    Decrypt_Data(test, "test2");
    std::cout << test.toStdString() << "\n\n";
    Encrypt_Data(test,"test2");
    Decrypt_Data(test,"test");

    std::cout << "Test 4(E=test2, D=test) : \n";
    std::cout << "Decrypted : " << test.toStdString() << "\n\n";

    std::cout << "Test 5(E=test3) : \n";
    Encrypt_Data(test,"test3");
    std::cout << "Encrypted : " << test.toStdString() << "\n";

    std::cout << "End Test\n";
}

//Création d'une nouvelle clé de cryptage ayant pour nom "name" et suivant le mot de passe "password"
//le "password" doit être >= au codeSize
bool CryptoFire::Add_Encrypted_Key(QString name, QString password, QString key)
{
    for(int i=0;i<_EncryptedKeys.count();i++) {
        if(_EncryptedKeys.at(i).contains(name)) {
            throw sameName;
        }
    }
    if(password.count() < _codeSize) {
        throw codeSize;
    }

    if(key.isEmpty()) {
        key = _key;
    }

    if(key.count() != _key.count()) {
        throw badKey;
    }


    QString result = Encrypt_Key(password, key);
    if(result == nullptr) {
        throw  unknown;
    }

    _EncryptedKeys.append(name + "|" + result);
    qDebug() << "Key to hex(" + name + ") : " + Key_To_SHA256(name);
    return true;
}

//Suppression de la clé de cryptage "name"
bool CryptoFire::Remove_Encrypted_Key(QString name)
{
    for(int i=0;i<_EncryptedKeys.count();i++) {
        if(_EncryptedKeys.at(i).contains(name)) {
            _EncryptedKeys.removeAt(i);
            return true;
        }
    }
    return false;
}

//Décryptage des données "data" avec la clé correspondante "name"
void CryptoFire::Decrypt_Data(QString &data, QString name)
{
    //Obtention de la clé de cryptage
    QString k;
    for(int i=0;i<_EncryptedKeys.count();i++) {
        if(_EncryptedKeys.at(i).split("|").first() == name) {
            k = _EncryptedKeys.at(i).split("|").last();
        }
    }
    if(k.isEmpty()) {
        data = "Error key not found";
        return;
    }

    //Décryptage des données
    QString decrypt;
    int idk(0);
    for(int i = 0;i<data.count();i++)
    {
        if(idk == k.count())
        {
            idk = 0;
        }
        long t = data.at(i).unicode();
        if(t == _charSize + 1)//retour a '
        {
            t = 34;
        }
        else if(t == _charSize + 2)//retour a "
        {
            t = 39;
        }
        t += k.at(idk).unicode();
        if(t < 0)
        {
            t = t + _charSize;
        }
        else if(t > _charSize)
        {
            t = t - _charSize;
        }
        //qDebug() << "Key :" << k.at(idk).unicode() << " original : " << data.at(i).unicode() << " result : " << t;
        decrypt += QChar((int)t);
        idk++;
    }

    emit Decrypted_Data(decrypt);
    data = decrypt;
}

//Cryptage des données "data" avec la clé correspondante "name"
void CryptoFire::Encrypt_Data(QString &data, QString name)
{
    //Obtention de la clé de cryptageqDebug() << ekey << ekey.count();
    QString k;
    for(int i=0;i<_EncryptedKeys.count();i++) {
        if(_EncryptedKeys.at(i).split("|").first() == name) {
            k = _EncryptedKeys.at(i).split("|").last();
        }
    }
    if(k.isEmpty()) {
        data = "Error key not found";
        return;
    }

    //Cryptage des données
    QString crypt;
    int idk(0);
    for(int i = 0;i<data.count();i++)
    {
        if(idk == k.count())
        {
            idk = 0;
        }
        long t = data.at(i).unicode();
        t -= k.at(idk).unicode();
        if(t > _charSize)
        {
            t = t - _charSize;
        }
        else if(t < 0)
        {
            t = t + _charSize;
        }
        if(t == 34)//si '
        {
            t = _charSize + 1;
        }
        else if(t == 39)//ou "
        {
            t = _charSize + 2;
        }
        //qDebug() << "Key :" << k.at(idk).unicode() << " original : " << data.at(i).unicode() << " result : " << t;
        crypt += QChar((int)t);
        idk++;
    }

    emit Encrypted_Data(crypt);
    data = crypt;
}

//Génération de la clé original de la taille "keySize"
//Clé généré par le serveur
//Cette clé sera transmise au clients
void CryptoFire::Generate_Key(int keySize)
{
    srand(static_cast<uint>(QTime::currentTime().msec()));
    QString key;

    for(int i = 0;i<keySize;i++)
    {
        key.append(QChar(rand() % _charSize));
    }
    _key = key;
}

//Génération d'une nouvelle clé suivant le mot de passe et la clé original
//Clé privé non transmise, sera utilisé pour crypter/décrypter les données
//Clé généré par le client et le serveur
QString CryptoFire::Encrypt_Key(QString password, QString key)
{
    //le mot de passe  doit être minimum de taille identique au "codeSize"
    if(password.count() < _codeSize) {
        return "Error : WebPassword is too short !";
    }

    if(key.isEmpty()) {
        key = _key;
    }

    //Convertion password to sha256
    password = QCryptographicHash::hash(password.toLatin1(),QCryptographicHash::Sha256).toHex();
    qDebug() << "Password hashed to hex : " << password;

    //Génération du code
    int code[_codeSize];
    for(int i=0;i<_codeSize;i++) {
        code[i] = 0;
    }

    int split = password.count() / _codeSize;
    int act = 0;
    for(int i=0;i<password.count();i++) {
        act++;
        if(act > split)
            act = 0;
        code[i / split] += password.at(i).unicode();
    }
    for(int i=0;i<_codeSize;i++) {
        code[i] = code[i] % 3;
    }

    QString codevalue;
    for(int i=0;i<_codeSize;i++)
        codevalue.append(code[i]);
    qDebug() << "Generate key - Code : " << codevalue;

    //Génération de la clé suivant code et password
    QString ekey;
    int intCode = 0;
    int intPassword = 0;
    for(int i = 0;i<key.count();i++) {
        unsigned int tchar = 0;
        if(code[intCode] == 0) {
            tchar = static_cast<unsigned int>(key.at(i).unicode() + password.at(intPassword).unicode());
        }
        else if(code[intCode] == 1) {
            tchar = static_cast<unsigned int>(key.at(i).unicode() - password.at(intPassword).unicode());
        }
        else if(code[intCode] == 2) {
            tchar = static_cast<unsigned int>(key.at(i).unicode() * password.at(intPassword).unicode());
        }
        else if(code[intCode] == 3) {
            tchar = static_cast<unsigned int>(key.at(i).unicode() / password.at(intPassword).unicode());
        }
        else {
            return "EncryptPKEY : Code is corrupted ! key not encrypted !";
        }

        //Modification de la valeur si supérieur à _charSize
        if(tchar > static_cast<unsigned int>(_charSize)) {
            tchar = tchar % _charSize;
        }

        //qDebug() << "Generate key - original : " << key.at(i).unicode() << " result : " << tchar;

        ekey += QChar(tchar);
        intCode++;
        if(intCode >= _codeSize) {
            intCode = 0;
        }
        intPassword++;
        if(intPassword >= password.count()) {
            intPassword = 0;
        }
    }

    if(ekey.count() == key.count()) {
        return ekey;
    }
    else {
        return nullptr;
    }
}

QString CryptoFire::Get_Encrypted_Key(QString name)
{
    for(int i=0;i<_EncryptedKeys.count();i++) {
        if(_EncryptedKeys.at(i).split("|").first() == name) {
            return _EncryptedKeys.at(i).split("|").last();
        }
    }
    return QString("");
}
