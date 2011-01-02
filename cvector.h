#ifndef CVECTOR_H
#define CVECTOR_H

class CVector {

protected:

	float m_values[3];

public:
    CVector();
    CVector( const CVector& );
    CVector( float , float , float );

    float*	array();

    float	x();
    float	y();
    float	z();

    void	setX( float );
    void	setY( float );
    void	setZ( float );

    void	set( float , float , float );

    void    normalize();

    float   length();

    CVector operator - ( CVector );

    void    operator = ( CVector v );

    void    operator * ( CVector v );

    float    angleFrom( CVector v );

    CVector  cross( CVector ) const;

    void    renderAsNormal();
};

#endif // CVECTOR_H
