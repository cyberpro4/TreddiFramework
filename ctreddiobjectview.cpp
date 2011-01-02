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

void CTreddiObjectView::customPaint( CRenderingInfo* rInfo ){
    CClassicView::customPaint( rInfo );
    CTreddiObject*  obj;
    foreach( obj , m_objs ){

        glPushMatrix();

        obj->render( rInfo );

        glPopMatrix();

    }

    CVector v(1,0,0);
    float ucsSize = rInfo->m_viewCenter.z() * 0.1;

    glColor3fv( v.array() );
    v.renderAsNormal( ucsSize );

    v.set( 0 , 1 , 0 );
    glColor3fv( v.array() );
    v.renderAsNormal( ucsSize );

    v.set( 0 , 0 , 1 );
    glColor3fv( v.array() );
    v.renderAsNormal( ucsSize );

}
