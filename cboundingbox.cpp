#include "cboundingbox.h"

CBoundingBox::CBoundingBox(){
    m_minPoint.set( 0xffff, 0xffff, 0xffff );
    m_maxPoint.set( -0xffff, -0xffff, -0xffff );
    m_pointNumber = 0;
}

void CBoundingBox::push( CVector v ){
    if( !m_pointNumber ){
        m_minPoint = v;
        m_maxPoint = v;
    }else{
        m_minPoint.set( qMin<float>( m_minPoint.x(), v.x() ),
                        qMin<float>( m_minPoint.y(), v.y() ),
                        qMin<float>( m_minPoint.z(), v.z() ) );
        m_maxPoint.set( qMax<float>( m_maxPoint.x(), v.x() ),
                        qMax<float>( m_maxPoint.y(), v.y() ),
                        qMax<float>( m_maxPoint.z(), v.z() ) );
    }
    m_pointNumber++;
}

void CBoundingBox::render(){
    glDisable( GL_LIGHTING );
    glColor3f( 1.0, 1.0 ,1.0 );
    float factor = 1.0;
    glBegin( GL_LINES );
        glVertex3f( m_minPoint.x()*factor, m_minPoint.y()*factor, m_minPoint.z()*factor );
        glVertex3f( m_minPoint.x()*factor, m_minPoint.y()*factor, m_maxPoint.z()*factor );

        glVertex3f( m_minPoint.x()*factor, m_minPoint.y()*factor, m_minPoint.z()*factor );
        glVertex3f( m_minPoint.x()*factor, m_maxPoint.y()*factor, m_minPoint.z()*factor );

        glVertex3f( m_minPoint.x()*factor, m_minPoint.y()*factor, m_minPoint.z()*factor );
        glVertex3f( m_maxPoint.x()*factor, m_minPoint.y()*factor, m_minPoint.z()*factor );


        glVertex3f( m_maxPoint.x()*factor, m_maxPoint.y()*factor, m_maxPoint.z()*factor );
        glVertex3f( m_maxPoint.x()*factor, m_maxPoint.y()*factor, m_minPoint.z()*factor );

        glVertex3f( m_maxPoint.x()*factor, m_maxPoint.y()*factor, m_maxPoint.z()*factor );
        glVertex3f( m_maxPoint.x()*factor, m_minPoint.y()*factor, m_maxPoint.z()*factor );

        glVertex3f( m_maxPoint.x()*factor, m_maxPoint.y()*factor, m_maxPoint.z()*factor );
        glVertex3f( m_minPoint.x()*factor, m_maxPoint.y()*factor, m_maxPoint.z()*factor );
    glEnd();
    glEnable( GL_LIGHTING );
}
