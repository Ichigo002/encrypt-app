#include "encryptmethods.h"
#include "MovData.h"
#include "exec_msg.h"

EncryptMethods::EncryptMethods()
{

}

int EncryptMethods::Exec_Binary(MovData _data, bool includeEnter, bool includeSpaces)
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

    int a = data.count();
    QVectorIterator<QString> iv(data);
    QString buff, data_line;
    data.clear();

    while(iv.hasNext())
    {
        //read next line
        buff = iv.next();
        data_line = "";

        //convert to bin
        for(int i=0; i < buff.length(); i++)
        {
            char c = buff.at(i).toLatin1();
            data_line += GetBinary(c);
            if(includeSpaces)
                data_line += " ";

        }
        // handling expections
        if(includeEnter && data.count()+1 < a)
        {
            data_line += "00001010";
            if(includeSpaces)
                data_line += " ";
        }
        //add result to vector
        data.push_back(data_line);
    }

    // Write down file with result
    return WriteDataFile(&data, _data.getTargetPath());

}

int EncryptMethods::Exec_Dec(MovData _data, bool includeSep)
{
    QVector<QString> data;

    //convert for file
    if(_data.getFilePath() != nullptr)
    {
        int status = ReadDataFile(&data, _data.getFilePath());
        if(status != SUCCEED)
            return status;
    }
    else if(_data.getTextEncode() != nullptr)
    {
        data.push_back(_data.getTextEncode());
    }
    else
    {
        return ERR_NO_INPUT;
    }

    int a = data.count();
    QVectorIterator<QString> iv(data);
    QString buff, __buff, data_line;
    data.clear();

    while(iv.hasNext())
    {
        //read next line
        buff = iv.next();
        data_line = "";

        //convert to bin
        for(int i=0; i < buff.length(); i++)
        {
            char c = buff.at(i).toLatin1();
            __buff = QString::number((int)c);
            if(includeSep)
                data_line += "-";
            else if(__buff.length() < 3)
            {
                int diff = 3 - __buff.length();
                for(int i=0; i < diff; i++)
                    data_line += "0";
            }
            data_line += __buff;
        }
        // handling expections
        if(data.count()+1 < a)
        {
            if(includeSep)
                data_line += "-10";
            else
                data_line += "010";
        }
        //add result to vector
        data.push_back(data_line);
    }

    return WriteDataFile(&data, _data.getTargetPath());
}

int EncryptMethods::Exec_Caesar(MovData _data, int key)
{
    QVector<QString> data;

    //convert for file
    if(_data.getFilePath() != nullptr)
    {
        int status = ReadDataFile(&data, _data.getFilePath());
        if(status != SUCCEED)
            return status;
    }
    else if(_data.getTextEncode() != nullptr)
    {
        data.push_back(_data.getTextEncode());
    }
    else
    {
        return ERR_NO_INPUT;
    }

    QVectorIterator<QString> iv(data);
    QString buff, data_line;
    data.clear();

    while(iv.hasNext())
    {
        //read next line
        buff = iv.next();
        data_line = "";

        //encrypt
        data_line += MoveStringAbout(buff, key);

        //add result to vector
        data.push_back(data_line);
    }

    return WriteDataFile(&data, _data.getTargetPath());
}

int EncryptMethods::Exec_Inverted(MovData _data, bool simWords)
{
    QVector<QString> data;

    //convert for file
    if(_data.getFilePath() != nullptr)
    {
        int status = ReadDataFile(&data, _data.getFilePath());
        if(status != SUCCEED)
            return status;
    }
    else if(_data.getTextEncode() != nullptr)
    {
        data.push_back(_data.getTextEncode());
    }
    else
    {
        return ERR_NO_INPUT;
    }

    //int ct = data.count();
    QVectorIterator<QString> iv(data);
    QString buff, data_line;
    data.clear();

    while(iv.hasNext())
    {
        //read next line
        buff = iv.next();
        data_line = "";

        //for lines
        if(simWords)
        {
            QStringList words;
            words = buff.split(" ");
            for(int i=0; i < words.count(); i++)
            {
                data_line += InvertQString(words.at(i)) + " ";
            }
        }
        else
        {
            data_line += InvertQString(buff);
        }


        //add result to vector
        data.push_back(data_line);
    }

    return WriteDataFile(&data, _data.getTargetPath());
}

QString EncryptMethods::GetBinary(char c)
{
    QString s;
    for (int i = 7; i >= 0; --i)
    {
        s += ((c & (1 << i))? '1' : '0');
    }
    return s;
}

int EncryptMethods::ReadDataFile(QVector<QString> *v, QString path)
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

int EncryptMethods::WriteDataFile(QVector<QString> *v, QString path)
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

QString EncryptMethods::InvertQString(QString str)
{
    QString r = "";
    int l = str.length() - 1;
    for(int i=0; i <= l; i++)
        r.append(str.at(l - i));
    return r;
}

QString EncryptMethods::MoveStringAbout(QString org, int key)
{
    QString s="";

    for(int i=0; i < org.length(); i++)
    {
        char c = org.at(i).toLatin1();
        int d = int(c);
        if(d != 10)
        {
            d += key;
        }
        s += char(d);
    }
    return s;
}


