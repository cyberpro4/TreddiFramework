#include "ctreddiobject.h"
#include <QtOpenGL>

CTreddiObject::CTreddiObject(){
}

void CTreddiObject::render(){
    glPushMatrix();

    glRotatef( m_rotation.x(), 1.0, 0.0, 0.0);
    glRotatef( m_rotation.y(), 0.0, 1.0, 0.0);
    glRotatef( m_rotation.z(), 0.0, 0.0, 1.0);
    glTranslatef( m_position.x() , m_position.y() , m_position.z() );

    customRender();
    m_boundingBox.render();

    glPopMatrix();
}

CVector* CTreddiObject::position(){
    return &m_position;
}

CVector* CTreddiObject::rotation(){
    return &m_rotation;
}
