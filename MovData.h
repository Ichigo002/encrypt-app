#ifndef MOVDATA_H
#define MOVDATA_H

#include <QString>

class MovData
{
public:
    MovData(QString fpath = nullptr, QString tpath = nullptr, QString txt = nullptr)
    {
        fpath = file_path;
        tpath = target_path;
        text = txt;
    }


    ~MovData() { ; }

    void setFilePath(QString p) { file_path = p; }
    void setTargetPath(QString p) { target_path = p; }
    void setTextEncode(QString p) { text = p; }

    QString getFilePath() { return file_path; }
    QString getTargetPath() { return target_path; }
    QString getTextEncode() { return text; }

private:
    QString file_path;
    QString target_path;
    QString text;

};

#endif // MOVDATA_H
