#include "decryptmethods.h"
#include "exec_msg.h"

DecryptMethods::DecryptMethods()
{

}

int DecryptMethods::Exec_Binary(MovData _data)
{
    QVector<QString> data;

    if(_data.getFilePath() != nullptr)
    {
        int status = ReadDataFile(&data, _data.getFilePath());
        if(status != SUCCEED)
            return status;
    }
    else if (_data.getTextEncode() != nullptr)
    {
        data.push_back(_data.getTextEncode());
    }
    else
    {
        return ERR_NO_INPUT;
    }

    //int a = data.count();
    QVectorIterator<QString> iv(data);
    QString buff, data_line;
    data.clear();

    while(iv.hasNext())
    {
        //read next line
        buff = iv.next();
        data_line = "";

        //DECRYPTING...

        QVector<QString> bytes;
        QString buff;
        QString null = "";
        null += (char)0;

        int st = SplitBinaryArray(&buff, &bytes);
        if(st != SUCCEED)
            return st;

        for(int i=0; i< bytes.count(); i++)
        {
            qDebug() << "BYTE "<<i<<": "<<bytes.at(i);
            buff = (char)ByteToDec(bytes.at(i));
            if(buff == null)
                qDebug()<<"NULL!!!";
            data_line += buff;
        }

        data.push_back(data_line);
    }

    return WriteDataFile(&data, _data.getTargetPath());
}

int DecryptMethods::ReadDataFile(QVector<QString> *v, QString path)
{
    QFile file(path);
    if(!file.exists())
    {
        return ERR_FILE_NOT_EXIST;
    }
    if(file.open(QIODevice::ReadOnly))
    {
        QTextStream stream(&file);
        QString buffer;

        while(!stream.atEnd())
        {
            buffer = stream.readLine();
            v->push_back(buffer);
        }

        file.close();
        return SUCCEED;
    }
    else
    {
        return ERR_OPEN_READ;
    }
}

int DecryptMethods::WriteDataFile(QVector<QString> *v, QString path)
{
    if(path == nullptr || path == "" || !path.contains(".txt"))
        return ERR_BAD_PATH;

    QFile file(path);

    if(file.open(QIODevice::WriteOnly))
    {
        QTextStream stream(&file);
        QVectorIterator<QString> iv(*v);
        QString data_line;

        while(iv.hasNext())
        {
            data_line = iv.next();
            stream << data_line << Qt::endl;
        }

        file.flush();
        file.close();
        return SUCCEED;
    }
    else
    {
        return ERR_OPEN_WRITE;
    }
}

int DecryptMethods::SplitBinaryArray(QString* array, QVector<QString>* out)
{
    if(array->contains(' '))
    {
        if(array->length() % 9 != 0)
            return ERR_INVALID_BIN;
    }
    else
    {
        if(array->length() % 8 != 0)
            return ERR_INVALID_BIN;
    }

    int bytes = array->length() / 8;

    QString byte;

    for(int i=0; i < array->length(); i++)
    {
        if(array->at(i) == ' ')
        {
            array->remove(i,1);
        }
    }

    int st = CheckArray(array, "01");
    if(st != SUCCEED)
        return st;

    for(int i=0; i < bytes; i++)
    {
        byte="";
        for(int j=8*i; j < 8*i+8; j++)
        {
            byte += array->at(j);
        }

        out->push_back(byte);
    }

    return SUCCEED;
}

int DecryptMethods::CheckArray(QString* array, QString allowChars)
{
    bool acc;
    for(int i=0; i < array->length(); i++)
    {
        acc = false;
        for(int j=0; j< allowChars.length(); j++)
        {
            if(array->at(i) == allowChars.at(j))
                acc = true;
        }
        if(!acc)
        {
            return ERR_INVALID_BIN;
        }
    }

    return SUCCEED;
}

int DecryptMethods::ByteToDec(QString byte)
{
    int sum = 0;
    for(int i=0; i < 8; i++)
    {
        if(byte.at(7-i) == '1')
        {
            sum += pow(2, i);
        }
    }
    return sum;
}
