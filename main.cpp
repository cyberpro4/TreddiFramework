#include <QtGui/QApplication>
#include "cpixelviewer.h"
#include "matchertmp.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    /*CPixelViewer w;
    w.show();*/

    MatcherTmp  tmp;

    return a.exec();
}
