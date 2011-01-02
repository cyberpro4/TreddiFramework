#include "cplane.h"
#include <QtOpenGL>

CPlane::CPlane(){
}

CPlane::CPlane( const CVector & v , float d ) {
    m_normal = v;
    m_distance = d;
}

void CPlane::render(){
    CVector u( 1,0,0 );

    if( m_normal == u ){
        u.set( 0 , 1 , 0 );
    }

    CVector v;

    u = u.cross( m_normal );
    u.normalize();

    v = u.cross( m_normal );
    v.normalize();

    CVector t;

    t = m_normal * m_distance;
    glTranslatef( t.x() , t.y(), t.z() );
    glBegin( GL_QUADS );

    t = u + v;
    glVertex3fv( t.array() );

    t = ( u * -1 ) + v;
    glVertex3fv( t.array() );

    t = ( u * -1 ) - v;
    glVertex3fv( t.array() );

    t = u - v;
    glVertex3fv( t.array() );

    glEnd();

    glColor3f(1,0,0);
    m_normal.renderAsNormal();
}
