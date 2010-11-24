#include "cvector.h"

CVector::CVector(){
	m_values[0] = m_values[1] = m_values[2] = 0;
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

void	CVector::set( float a , float b , float c  ){
	m_values[0] = a;
	m_values[1] = b;
	m_values[2] = c;
}
