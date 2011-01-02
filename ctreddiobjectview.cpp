#include "ctreddiobjectview.h"
#include "cplane.h"

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

    CVector v(1,0,0);

    glColor3fv( v.array() );
    v.renderAsNormal();

    v.set( 0 , 1 , 0 );
    glColor3fv( v.array() );
    v.renderAsNormal();

    v.set( 0 , 0 , 1 );
    glColor3fv( v.array() );
    v.renderAsNormal();

}
