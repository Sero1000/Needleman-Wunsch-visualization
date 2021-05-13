#include "dp_visualiser.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DP_Visualiser w;
    w.show();
    return a.exec();
}
