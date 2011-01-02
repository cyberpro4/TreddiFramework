#ifndef CSPHEREOBJECT_H
#define CSPHEREOBJECT_H

#include <QtOpenGL>
#include "ctreddiobject.h"

class CSphereObject : public CTreddiObject {

protected:

    GLUquadricObj*  m_glQuadric;

    float   m_radius;

public:

    CSphereObject( float radius = 10 );

    virtual void customRender( CRenderingInfo* );

};

#endif // CSPHEREOBJECT_H
