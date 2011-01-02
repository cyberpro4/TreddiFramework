#ifndef CRENDERINGINFO_H
#define CRENDERINGINFO_H

#include "cvector.h"

class CRenderingInfo{

public:

    CVector     m_viewCenter;
    CVector     m_viewRotation;

public:
    CRenderingInfo();
};

#endif // CRENDERINGINFO_H
