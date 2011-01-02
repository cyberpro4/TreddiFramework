#include "ctreddiobjectview.h"

CTreddiObjectView::CTreddiObjectView(){
}

void CTreddiObjectView::addTreddiObject( CTreddiObject *obj ){
    m_objs.append( obj );
}

void CTreddiObjectView::removeAllTreddiObject(){
    m_objs.clear();
}

void CTreddiObjectView::customPaint(){
    CClassicView::customPaint();
    CTreddiObject*  obj;
    foreach( obj , m_objs ){

        glPushMatrix();

        obj->render();

        glPopMatrix();

    }

}
