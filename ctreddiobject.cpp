#include "ctreddiobject.h"
#include <QtOpenGL>

CTreddiObject::CTreddiObject(){
}

void CTreddiObject::render( CRenderingInfo* rInfo ){
    glPushMatrix();

    glTranslatef( m_position.x() , m_position.y() , m_position.z() );

    customRender( rInfo );
    m_boundingBox.render();

    glPopMatrix();
}

CVector* CTreddiObject::position(){
    return &m_position;
}
