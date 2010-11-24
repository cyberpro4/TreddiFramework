#include "cpixelvector.h"

CPixelVector::CPixelVector(){
}

CPixelVector::CPixelVector(float a,float b,float c,QColor ch) : CVector( a,b,c ){
	m_color = ch;
}

QColor	CPixelVector::color(){
	return m_color;
}

void	CPixelVector::setColor( QColor ch ){
	m_color = ch;
}
