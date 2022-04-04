#ifndef ENCRYPTMETHODS_H
#define ENCRYPTMETHODS_H

#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QVector>
#include "MovData.h"

class EncryptMethods
{
public:

    EncryptMethods();

    int Exec_Binary(MovData _data, bool includeEnter, bool includeSpaces);

    int Exec_Dec(MovData _data, bool includeSep);

    int Exec_Caesar(MovData _data, int key);

    int Exec_Inverted(MovData _data, bool simWords);

private:

    int ReadDataFile(QVector<QString> *v, QString path);
    int WriteDataFile(QVector<QString> *v, QString path);

    QString GetBinary(char c);
    QString InvertQString(QString str);
    QString MoveStringAbout(QString org, int key);

};

#endif // ENCRYPTMETHODS_H
