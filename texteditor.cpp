#include "texteditor.h"
#include "ui_texteditor.h"
#include "encoderapp.h"

TextEditor::TextEditor(EncoderApp *en, QString txt, bool encrypt, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TextEditor)
{
    ui->setupUi(this);
    encoder = en;
    this->encrypt = encrypt;
    if(txt != nullptr)
    {
        ui->textEdit->setText(txt);
    }
}

TextEditor::~TextEditor()
{
    delete ui;
}

void TextEditor::on_buttonBox_accepted()
{
    encoder->on_click_accepted_texteditor(ui->textEdit->toPlainText(), encrypt);
}

