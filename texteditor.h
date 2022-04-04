#ifndef TEXTEDITOR_H
#define TEXTEDITOR_H

#include <QDialog>
#include "encoderapp.h"

namespace Ui {
class TextEditor;
}

class TextEditor : public QDialog
{
    Q_OBJECT

public:
    explicit TextEditor(EncoderApp *en, QString txt, bool encrypt,  QWidget *parent = nullptr);
    ~TextEditor();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::TextEditor *ui;
    EncoderApp *encoder;
    bool encrypt;
};

#endif // TEXTEDITOR_H
