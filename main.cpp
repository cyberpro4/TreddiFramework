#include <QtGui/QApplication>
#include "ctreddiobjectview.h"
#include "csphereobject.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CTreddiObjectView   view;
    CSphereObject   sph( 10 );
    view.addTreddiObject( &sph );
    view.show();

    return a.exec();
}
