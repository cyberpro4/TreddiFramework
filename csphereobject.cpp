#include "csphereobject.h"

CSphereObject::CSphereObject( float rad ){

    m_glQuadric = gluNewQuadric();
    gluQuadricDrawStyle( m_glQuadric , GL_FILL );

    m_radius = rad;
}

void CSphereObject::customRender(){

    gluSphere( m_glQuadric , m_radius , 10 , 10 );

}
