// Vector.h: interface for the CVector class.
//
//////////////////////////////////////////////////////////////////////

# ifndef _VECTOR_H
# define _VECTOR_H

class CPoint3D;

class CVector
{
public:
	
	// Object Constructors
	CVector();
	CVector(CPoint3D position);
	CVector(float dx, float dy, float dz);
	
	// Object destruction
	virtual ~CVector();

	// Object interface
	void	 SetVector	(float dx, float dy, float dz);
	CVector& Normalize	();

	float	Magnitude	() const;
	float	XComponent	() const;
	float	YComponent	() const;
	float	ZComponent	() const;
	
	float	DotProduct		(CVector vector1);
	CVector CrossProduct	(CVector that);
	CVector	GetOrthoAlong	(CVector approxDirection);

	CVector operator* (float fScale);
	CVector operator- (const CVector& that);
    CVector operator+ (const CVector& that);
    CVector& operator=(const CPoint3D& point);

protected:
	float m_fdx;
	float m_fdy;
	float m_fdz;
};

# endif