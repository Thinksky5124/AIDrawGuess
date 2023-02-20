#include "AIDrawGuess.h"
#include <QtWidgets/QApplication>

#include "onnxruntime_cxx_api.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    AIDrawGuess w;
    w.show();
    return a.exec();
}
