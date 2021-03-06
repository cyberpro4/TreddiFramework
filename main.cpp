#include <QtGui/QApplication>
#include "ctreddiobjectview.h"
#include "csphereobject.h"
#include "c3dsmodel.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    CTreddiObjectView   view;

    //CSphereObject   sph( 1000 );
    //view.addTreddiObject( &sph );
//qDebug() << Q_FUNC_INFO << " " << __LINE__;
    C3DSModel model("./tree.3DS");
    view.addTreddiObject( &model );

    view.show();

    return a.exec();
}
