#include "csphereobject.h"

CSphereObject::CSphereObject( float rad ){

    m_glQuadric = gluNewQuadric();
    gluQuadricDrawStyle( m_glQuadric , GL_FILL );

    m_radius = rad;

    m_boundingBox.push( CVector( -rad,-rad,-rad ) );
    m_boundingBox.push( CVector( rad,rad,rad ) );
}

void CSphereObject::customRender( CRenderingInfo* rInfo ){

    gluSphere( m_glQuadric , m_radius , 10 , 10 );

}
