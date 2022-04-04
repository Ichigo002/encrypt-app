#ifndef DECRYPTMETHODS_H
#define DECRYPTMETHODS_H

#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QVector>
#include <QtMath>
#include "MovData.h"

class DecryptMethods
{
public:
    DecryptMethods();

    int Exec_Binary(MovData _data);

    int Exec_Dec(MovData _data);

    int Exec_Caesar(MovData _data, int key);

    int Exec_Inverted(MovData _data, bool simWords);

private:

    int ReadDataFile(QVector<QString> *v, QString path);
    int WriteDataFile(QVector<QString> *v, QString path);

    int SplitBinaryArray(QString* array, QVector<QString>* out);
    int CheckArray(QString* array, QString allowChars);
    int ByteToDec(QString byte);
};

#endif // DECRYPTMETHODS_H
