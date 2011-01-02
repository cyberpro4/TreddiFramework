#ifndef CBOUNDINGBOX_H
#define CBOUNDINGBOX_H

#include <QtCore>
#include <QtOpenGL>
#include "cvector.h"

class CBoundingBox{
public:
    CBoundingBox();

    void push( CVector v );

    void render();

private:
    CVector m_minPoint;
    CVector m_maxPoint;

    int     m_pointNumber;  //numero di punti che hanno generato la box
};

#endif // CBOUNDINGBOX_H

