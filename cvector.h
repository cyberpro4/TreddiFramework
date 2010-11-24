#ifndef CVECTOR_H
#define CVECTOR_H

class CVector {

protected:

	float m_values[3];

public:
    CVector();
	CVector( float , float , float );

	float*	array();

	float	x();
	float	y();
	float	z();

	void	setX( float );
	void	setY( float );
	void	setZ( float );

	void	set( float , float , float );
};

#endif // CVECTOR_H
