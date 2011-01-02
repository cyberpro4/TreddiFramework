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

    CVector operator + ( CVector ) const;

    CVector operator - ( CVector ) const;

    void    operator = ( CVector v );

    bool    operator == ( CVector v) const;

    void    operator * ( CVector v );
    CVector operator * ( float v ) const;

    float    angleFrom( CVector v );

    CVector  cross( CVector ) const;

    void    renderAsNormal( float size = 1 );
};

#endif // CVECTOR_H
