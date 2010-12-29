#include "ctreddiobject.h"
#include <QtOpenGL>

CTreddiObject::CTreddiObject()
{
}

void CTreddiObject::render(){
    glPushMatrix();

    glTranslatef( m_position.x() , m_position.y() , m_position.z() );

    customRender();

    glPopMatrix();
}
