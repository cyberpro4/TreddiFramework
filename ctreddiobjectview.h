#ifndef COBJECTVIEW_H
#define COBJECTVIEW_H

#include "cclassicview.h"
#include "ctreddiobject.h"

class CTreddiObjectView : public CClassicView  {

protected:

    QList<CTreddiObject*>   m_objs;

public:

    CTreddiObjectView();

    void    addTreddiObject( CTreddiObject* );
    void    removeAllTreddiObject();

    virtual void customPaint( CRenderingInfo* );

};

#endif // COBJECTVIEW_H
