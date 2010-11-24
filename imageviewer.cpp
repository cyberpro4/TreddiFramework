#include "imageviewer.h"

ImageViewer::ImageViewer( QImage im ){
    setPixmap( QPixmap::fromImage( im ) );
    show();
}
