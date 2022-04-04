#ifndef ENCODERAPP_H
#define ENCODERAPP_H

#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class EncoderApp; }
QT_END_NAMESPACE

class EncoderApp : public QMainWindow
{
    Q_OBJECT

public:
    enum ComboChoose
    {
        BINARY = 0,
        DEC = 1,
        CAESAR = 2,
        INVERTED = 3,
    };

    EncoderApp(QWidget *parent = nullptr);
    ~EncoderApp();
    void on_click_accepted_texteditor(QString txt, bool encrypt);

private slots:
    /*Encode mode*/
    void on_btn_en_loadFile_clicked();
    void on_btn_en_enterText_clicked();
    void on_btn_en_preview_clicked();
    void on_btn_en_code_clicked();
    void on_comboBox_en_type_currentIndexChanged(int index);

    /*Decode mode*/
    void on_btn_de_load_clicked();
    void on_btn_de_enterText_clicked();
    void on_btn_de_code_clicked();

    /*BOTH*/
    void HandleException(int exp);

private:
    /*Encoder*/
    //0 - no input, 1 - file input, 2 - text input
    void SetStyleInput(int active);

    QString file_path;
    QString text;
    /*Decoder*/
    //0 - no input, 1 - file input, 2 - text input
    void SetStyleInput_de(int active);

    QString file_path_de;
    QString text_de;

    /*Both*/
    Ui::EncoderApp *ui;

};
#endif // ENCODERAPP_H
