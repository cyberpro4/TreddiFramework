#ifndef CTREDDIOBJECT_H
#define CTREDDIOBJECT_H

#include "cvector.h"
#include "crenderinginfo.h"
#include "cboundingbox.h"

class CTreddiObject {

protected:

    CVector         m_position;

    CBoundingBox    m_boundingBox;

public:

    CTreddiObject();

    void    render( CRenderingInfo* );

    virtual void customRender( CRenderingInfo* ){}

    CVector *position();

};

#endif // CTREDDIOBJECT_H
