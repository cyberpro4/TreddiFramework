#ifndef CPLANE_H
#define CPLANE_H

#include "cvector.h"

class CPlane {

protected:

    CVector     m_normal;
    float       m_distance;

public:

    CPlane();
    CPlane( const CVector& , float );

    void    render();

};

#endif // CPLANE_H
