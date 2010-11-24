#include "matcher.h"
#include "imageviewer.h"

Matcher::Matcher(QImage im1 , QImage im2 ){
    m_image[0] = im1;
    m_image[1] = im2;

    m_patternSize = QSize( (m_image[0].width() * 0.053)+1 ,
                           (m_image[0].width() * 0.053)+1 );
    m_border = m_patternSize.width() / 2;
}

void    Matcher::pickPattern(QImage *image, QImage *pattern, QPoint location){

    int     _px = 0,_py = 0;
    uchar*  image_line = 0;
    uchar*  pattern_line = 0;

    for(    int __y = location.y() - (m_patternSize.height() / 2);
            __y < ( location.y() + m_patternSize.height() / 2 ); __y++ ){

        _px = 0;
        image_line = image->scanLine( __y );
        pattern_line = pattern->scanLine( _py );

        for( int __x = location.x() - (m_patternSize.width() / 2 );
                __x < ( location.x() + m_patternSize.width() / 2 ); __x++ ){

            //pattern->setPixel( _px , _py , image->pixel( __x , __y ) );
            pattern_line[ (_px * 3 ) ] = image_line[ __x * 3 ];
            _px++;
        }

        _py++;
    }
}

unsigned long    Matcher::diffPattern(QImage *p1, QImage *p2){

    unsigned long res = 0;
    uchar*  p1_line = 0;
    uchar*  p2_line = 0;

    for(    int __y = 0 ; __y < ( p1->size().height() ); __y+= (m_image[0].width() * 0.0053)+1 ){

        p1_line = p1->scanLine( __y );
        p2_line = p2->scanLine( __y );

        for( int __x = 0; __x < ( p1->size().width() ); __x+= (m_image[0].width() * 0.0053)+1 ){

            /*QRgb px1 = p1->pixel( QPoint( __x , __y ) );
            QRgb px2 = p2->pixel( QPoint( __x , __y ) );

            res += qAbs( qRed( px1 ) - qRed( px2 ) );
            res += qAbs( qGreen( px1 ) - qGreen( px2 ) );
            res += qAbs( qBlue( px1 ) - qBlue( px2 ) );*/
            res += qAbs( p1_line[ (__x * 3) + 0 ] - p2_line[ (__x * 3) + 0 ] );
            res += qAbs( p1_line[ (__x * 3) + 1 ] - p2_line[ (__x * 3) + 1 ] );
            res += qAbs( p1_line[ (__x * 3) + 2 ] - p2_line[ (__x * 3) + 2 ] );
        }

    }

    return res;
}

QPoint   Matcher::searchMatch(QPoint point ){

    pickPattern( &m_image[0] , &m_searchMatchPatt[0] , point );

    unsigned long minDiff = 0xFFFFFFFF;
    unsigned long minDiff_x = 0;
    unsigned long curDiff;

    for( int __x = ( point.x() - ( m_maxSearchX / 2.0 ) );
            __x < (m_maxSearchX/2) + point.x() ; __x+=1 ){

        if( __x < m_border || __x > m_image[1].width() - m_border ) continue;

        pickPattern( &m_image[1] , &m_searchMatchPatt[1] , QPoint( __x , point.y() ) );

        curDiff = diffPattern( &m_searchMatchPatt[0] , &m_searchMatchPatt[1] );
        if( curDiff < minDiff ){
            minDiff = curDiff;
            minDiff_x = __x;
        }
    }

    return QPoint( minDiff_x , point.y() );
}

void    Matcher::calculate( ){

    CPixelViewer *vvv = new CPixelViewer();

    QTime timer;
    timer.start();

    QSize size = m_image[0].size();
    qDebug() << size;

    m_searchMatchPatt[0] = QImage(m_patternSize , QImage::Format_RGB888 );
    m_searchMatchPatt[1] = QImage(m_patternSize , QImage::Format_RGB888 );

    QImage* imres = new QImage( size , QImage::Format_RGB888 );

    m_maxSearchX = size.width() / 8;

    for( int __y = m_border; __y < ( size.height() - m_border ); __y+= (size.width() * 0.01)+1 ){

        for( int __x = m_border; __x < ( size.width() - m_border ); __x+= (size.width() * 0.01)+1 ){
            int z = __x - searchMatch( QPoint( __x , __y ) ).x();

            if( qAbs( z ) < 100 ){
                m_pointList.append(
                        CPixelVector( __x , __y , z*6 ,
                            QColor( m_image[0].pixel( __x , __y ) ) ) );
            }

            int val = qAbs( (z * 255) / size.width() );
            if( val < 100 ){
                val *= 10;
                imres->setPixel( __x , __y , qRgb( val ,val ,val ) );
            }
        }

        qDebug() << "AT Y " << __y << " OF " << size.height() ;

    }

    qDebug() << " DONE: " << timer.elapsed() << "ms";

    vvv->setPixelList( &m_pointList );
    vvv->show();
    new ImageViewer( *imres );


}
