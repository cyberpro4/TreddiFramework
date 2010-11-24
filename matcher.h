#ifndef MATCHER_H
#define MATCHER_H

#include <QtGui>
#include "cvector.h"
#include "imageviewer.h"
#include "cpixelviewer.h"

class Matcher{

public:
    Matcher( QImage im1, QImage im2  );

    void    calculate();

protected:

    QImage  m_image[2];
    QImage  m_searchMatchPatt[2];

    int     m_border;
    int     m_maxSearchX;
    QSize   m_patternSize;

    void        pickPattern( QImage* image , QImage* pattern , QPoint location );
    QPoint      searchMatch( QPoint );
    unsigned long        diffPattern( QImage* p1 , QImage* p2 );

private:

    QList<CPixelVector> m_pointList;

};

#endif // MATCHER_H
