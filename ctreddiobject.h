#ifndef CTREDDIOBJECT_H
#define CTREDDIOBJECT_H

#include "cvector.h"

class CTreddiObject {

protected:

    CVector     m_position;

public:

    CTreddiObject();

    void    render();

    virtual void customRender(){}

};

#endif // CTREDDIOBJECT_H
