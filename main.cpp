#include "fridgeexplorer.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Fridgeexplorer w;
    w.show();

    return a.exec();
}
