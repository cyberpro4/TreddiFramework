#ifndef CPIXELVECTOR_H
#define CPIXELVECTOR_H

#include "cvector.h"
#include <QColor>

class CPixelVector : public CVector {

protected:

	QColor	m_color;

public:
    CPixelVector();
	CPixelVector(float,float,float,QColor);

	QColor	color();
	void	setColor( QColor );
};

#endif // CPIXELVECTOR_H
