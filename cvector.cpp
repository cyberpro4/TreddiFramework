#include "cvector.h"
#include <math.h>
#include <QtOpenGL>

CVector::CVector(){
	m_values[0] = m_values[1] = m_values[2] = 0;
}

CVector::CVector( const CVector& v ){
    m_values[0] = v.m_values[0];
    m_values[1] = v.m_values[1];
    m_values[2] = v.m_values[2];
}

CVector::CVector( float a , float b , float c  ){
	m_values[0] = a;
	m_values[1] = b;
	m_values[2] = c;
}

float*	CVector::array(){
	return m_values;
}

float	CVector::x(){
	return m_values[0];
}

float	CVector::y(){
	return m_values[1];
}

float	CVector::z(){
	return m_values[2];
}

void	CVector::setX( float v ){
	m_values[0] = v;
}

void	CVector::setY( float v ){
	m_values[1] = v;
}

void	CVector::setZ( float v ){
	m_values[2] = v;
}

float    CVector::length(){
    return sqrtf( (m_values[0]*m_values[0]) +
                  (m_values[1]*m_values[1]) +
                  (m_values[2]*m_values[2]) );
}

void    CVector::normalize(){
    float l = length();
    m_values[0] /= l;
    m_values[1] /= l;
    m_values[2] /= l;
}

float    CVector::angleFrom(CVector v){
    float l[3];

    l[0] = length();
    l[1] = v.length();
    l[2] = ( *this - v ).length();

    float a,b;
    a = ((l[0] * l[0]) + (l[1] * l[1]) - (l[2] * l[2]));
    b = 2 * l[0] * l[1];

    if( a == 0 || b == 0 )
        return 0;

    return acos( a / b );
}

CVector CVector::operator -( CVector v ) const {
    return CVector( m_values[0] - v.m_values[0] ,
                    m_values[1] - v.m_values[1] ,
                    m_values[2] - v.m_values[2] );
}

CVector CVector::operator + ( CVector v ) const {
    return CVector( m_values[0] + v.m_values[0] ,
                    m_values[1] + v.m_values[1] ,
                    m_values[2] + v.m_values[2] );
}

bool    CVector::operator == ( CVector v ) const {
    return m_values[0] == v.m_values[0] &&
            m_values[1] == v.m_values[1] &&
            m_values[2] == v.m_values[2];
}

void    CVector::operator =( CVector v ){
    m_values[0] = v.x();
    m_values[1] = v.y();
    m_values[2] = v.z();
}

CVector CVector::cross( CVector v ) const {
    return CVector( (m_values[1] * v.m_values[2]) - ( m_values[2] * v.m_values[1]),
                    (m_values[2] * v.m_values[0]) - ( m_values[0] * v.m_values[2]),
                    (m_values[0] * v.m_values[1]) - ( m_values[1] * v.m_values[0]) );
}

CVector CVector::operator *( float v ) const {
    return CVector( m_values[0] * v , m_values[1] * v , m_values[2] * v );
}

void    CVector::renderAsNormal( float size ){

    glPushMatrix();

        glDisable( GL_LIGHTING );
        glLineWidth( 3 );
        glBegin( GL_LINES );

        glVertex3f( 0,0,0 );
        CVector fv( *this );
        fv = fv * size;

        glVertex3fv( fv.array() );

        glEnd();

        glEnable( GL_LIGHTING );
    glPopMatrix();

}

void	CVector::set( float a , float b , float c  ){
	m_values[0] = a;
	m_values[1] = b;
	m_values[2] = c;
}
