#include "encoderapp.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    EncoderApp w;
    w.show();
    return a.exec();
}
