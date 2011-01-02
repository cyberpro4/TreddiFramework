#ifndef CTREDDIOBJECT_H
#define CTREDDIOBJECT_H

#include "cvector.h"
#include "crenderinginfo.h"
#include "cboundingbox.h"

class CTreddiObject {

protected:

    CVector         m_position;
    CVector         m_rotation;

    CBoundingBox    m_boundingBox;

public:

    CTreddiObject();

    void    render( CRenderingInfo* );

    virtual void customRender( CRenderingInfo* ){}

    CVector *position();
    CVector *rotation();

};

#endif // CTREDDIOBJECT_H
