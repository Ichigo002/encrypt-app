#include "encoderapp.h"
#include "ui_encoderapp.h"
#include "texteditor.h"
#include "encryptmethods.h"
#include "MovData.h"
#include "decryptmethods.h"
#include "exec_msg.h"

EncoderApp::EncoderApp(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::EncoderApp)
{
    ui->setupUi(this);

    file_path = nullptr;
    text = nullptr;
    SetStyleInput(0);
    SetStyleInput_de(0);

    // Add types of encoding
    QStringList types;

    types.push_back("Binary");
    types.push_back("Decimal");
    types.push_back("Caesar");
    types.push_back("Inverted");

    ui->comboBox_en_type->addItems(types);
    ui->comboBox_de_type->addItems(types);
}

EncoderApp::~EncoderApp()
{
    delete ui;
}

void EncoderApp::on_click_accepted_texteditor(QString txt, bool encrypt)
{
    if(encrypt)
        text = txt;
    else
        text_de = txt;
}

/***Encoder methods***/

void EncoderApp::on_btn_en_loadFile_clicked()
{
    file_path = QFileDialog::getOpenFileName(this, tr("Open file to encode"),                                       "/documents", tr("Text Files (*.txt)"));

    if(file_path != nullptr)
    {
        text = nullptr;
        SetStyleInput(1);
    }
}

void EncoderApp::on_btn_en_enterText_clicked()
{
    TextEditor editor(this, text, true);
    editor.exec();
    if(text == "")
    {
        text = nullptr;
        ui->btn_en_enterText->setStyleSheet("background-color: rgb(255, 80, 80);");

    }
    if(text != nullptr)
    {
        file_path = nullptr;
        SetStyleInput(2);
    }
}

void EncoderApp::on_btn_en_preview_clicked()
{
    //preview clicked
}

//0 - no input, 1 - file input, 2 - text input
void EncoderApp::SetStyleInput(int active)
{
    switch(active)
    {
    case 0: // no input
        ui->btn_en_loadFile->setStyleSheet("background-color: rgb(255, 80, 80);");
        ui->btn_en_enterText->setStyleSheet("background-color: rgb(255, 80, 80);");
        break;
    case 1: // file input
        ui->btn_en_loadFile->setStyleSheet("background-color: rgb(41, 175, 18);");
        ui->btn_en_enterText->setStyleSheet("background-color: rgb(255, 80, 80);");
        break;
    case 2: // text input
        ui->btn_en_loadFile->setStyleSheet("background-color: rgb(255, 80, 80);");
        ui->btn_en_enterText->setStyleSheet("background-color: rgb(41, 175, 18);");

        break;
    }
}

void EncoderApp::on_comboBox_en_type_currentIndexChanged(int index)
{
    ui->checkBox_en_bin_enter->setVisible(false);
    ui->checkBox_en_bin_spaces->setVisible(false);

    ui->checkBox_en_dec_space->setVisible(false);

    ui->label_ca_key->setVisible(false);
    ui->spinBox_ca_key->setVisible(false);

    ui->checkBox_en_inv_sentence->setVisible(false);

    switch(index)
    {
    case BINARY:
            ui->checkBox_en_bin_enter->setVisible(true);
            ui->checkBox_en_bin_spaces->setVisible(true);
        break;
    case DEC:
            ui->checkBox_en_dec_space->setVisible(true);
        break;
    case CAESAR: // Caesar
            ui->label_ca_key->setVisible(true);
            ui->spinBox_ca_key->setVisible(true);
        break;
    case INVERTED: // Inverted
            ui->checkBox_en_inv_sentence->setVisible(true);
        break;
    }
}

void EncoderApp::on_btn_en_code_clicked()
{
    EncryptMethods enm;
    MovData data;

    // retrieving data
    data.setFilePath(file_path);
    data.setTextEncode(text);

    int method = ui->comboBox_en_type->currentIndex();
    int returnState;
    QString target_path = QFileDialog::getSaveFileName(this, "Directory where encrypted file will be saved","encrypting-result.txt");
    data.setTargetPath(target_path);

    if(target_path == nullptr || target_path == "")
    {
        return;
        returnState = ERR_BAD_PATH;
    }
    else
    {
        //encoding starts
        switch(method)
        {
        case BINARY:
                returnState = enm.Exec_Binary(data, ui->checkBox_en_bin_enter->isChecked(), ui->checkBox_en_bin_spaces->isChecked());
            break;
        case DEC:
                returnState = enm.Exec_Dec(data, ui->checkBox_en_dec_space->isChecked());
            break;
        case CAESAR:
                returnState = enm.Exec_Caesar(data, ui->spinBox_ca_key->value());
            break;
        case INVERTED:
                returnState = enm.Exec_Inverted(data, ui->checkBox_en_inv_sentence->isChecked());
            break;
        default:
            QMessageBox::critical(this, "Uknown encoding method",
                                  "Index of unknown method: " + QString::number(method));
            return;
        }
    }

    HandleException(returnState);
}

/***Decode methods***/

void EncoderApp::on_btn_de_load_clicked()
{
    file_path_de = QFileDialog::getOpenFileName(this, tr("Open file to encode"),                                       "/documents", tr("Text Files (*.txt)"));

    if(file_path_de != nullptr)
    {
        text_de = nullptr;
        SetStyleInput_de(1);
    }
}

void EncoderApp::on_btn_de_enterText_clicked()
{
    TextEditor editor(this, text, false);
    editor.exec();
    if(text_de == "")
    {
        text_de = nullptr;
        ui->btn_de_enterText->setStyleSheet("background-color: rgb(255, 80, 80);");

    }
    if(text_de != nullptr)
    {
        file_path_de = nullptr;
        SetStyleInput_de(2);
    }
}

void EncoderApp::on_btn_de_code_clicked()
{
    DecryptMethods enm;
    MovData data;

    // retrieving data
    data.setFilePath(file_path_de);
    data.setTextEncode(text_de);

    int method = ui->comboBox_de_type->currentIndex();
    int returnState;
    QString target_path = QFileDialog::getSaveFileName(this, "Directory where encrypted file will be saved","encrypting-result.txt");
    data.setTargetPath(target_path);

    if(target_path == nullptr || target_path == "")
    {
        return;
        returnState = ERR_BAD_PATH;
    }
    else
    {
        //decrypting starts
        switch(method)
        {
        case BINARY:

                returnState = enm.Exec_Binary(data);
            break;
        case DEC:
                //returnState = enm.Exec_Dec(data);
            break;
        case CAESAR:
                //returnState = enm.Exec_Caesar(data, ui->spinBox_ca_key->value());
            break;
        case INVERTED:
                //returnState = enm.Exec_Inverted(data, ui->checkBox_en_inv_sentence->isChecked());
            break;
        default:
            QMessageBox::critical(this, "Uknown encoding method",
                                  "Index of unknown method: " + QString::number(method));
            return;
        }
    }

    HandleException(returnState);
}

void EncoderApp::HandleException(int exp)
{
    switch(exp)
    {
    case UNHANDLED:
        QMessageBox::critical(this, "Failed with code 2 [UNHANDLED]", "The program function did not handle the program at EncodingMethod::func(MovData data, ...)");
        break;
    case UNEXPECTED:
            QMessageBox::critical(this, "Failed with code 1 [UNEXPECTED]", "Program wasn't expecting return with code UNEXPECTED");
        break;
    case SUCCEED:
            //We made it bro!
        break;
    case ERR_FILE_NOT_EXIST:
            QMessageBox::critical(this, "Failed with code -1 [ERR_FILE_NOT_EXIST]", "File at: " + file_path + " doesn't exist or has been deleted.");
        break;
    case ERR_NO_INPUT:
            QMessageBox::critical(this, "Failed with code -2 [ERR_NO_INPUT]", "Input is empty or no options selected. Select 'Load file' or 'Enter Text'.");
        break;
    case ERR_OPEN_READ:
            QMessageBox::critical(this, "Failed with code -3 [ERR_OPEN_READ]", "Open file to read failed. Are you sure chosen file has extension *.txt?");
        break;
    case ERR_OPEN_WRITE:
            QMessageBox::critical(this, "Failed with code -4 [ERR_OPEN_WRITE]", "Open file to write code failed. Try reset program.");
        break;
    case ERR_BAD_PATH:
            QMessageBox::critical(this, "Failed with code -5 [ERR_BAD_PATH]", "Incorrect path to file to encode. Path is EMPTY.");
        break;
    case ERR_INVALID_BIN:
            QMessageBox::critical(this, "Failed with code -6 [ERR_INVALID_BIN]", "f");
        break;
    default:
        QMessageBox::critical(this, "App crashed with code " + QString::number(exp), "EROR");
        exit(EXIT_FAILURE);
    }
    return;
}

//0 - no input, 1 - file input, 2 - text input
void EncoderApp::SetStyleInput_de(int active)
{
    switch(active)
    {
    case 0: // no input
        ui->btn_de_load->setStyleSheet("background-color: rgb(255, 80, 80);");
        ui->btn_de_enterText->setStyleSheet("background-color: rgb(255, 80, 80);");
        break;
    case 1: // file input
        ui->btn_de_load->setStyleSheet("background-color: rgb(41, 175, 18);");
        ui->btn_de_enterText->setStyleSheet("background-color: rgb(255, 80, 80);");
        break;
    case 2: // text input
        ui->btn_de_load->setStyleSheet("background-color: rgb(255, 80, 80);");
        ui->btn_de_enterText->setStyleSheet("background-color: rgb(41, 175, 18);");

        break;
    }
}



