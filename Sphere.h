// Sphere.h: interface for the CSphere class.
//
//////////////////////////////////////////////////////////////////////

# ifndef _SPHERE_H
# define _SPHERE_H

# include "Shape.h"

class CSphere : public CShape  
{
public:
	
	// Constructors
	CSphere();
	CSphere(CPoint3D pos, CColor col, float radius);
	CSphere(CSphere &sphere1);

	// Object Interface
	CIntersectionInfo GetIntersection (CRay ray);
	void		SetRadius		(float radius)	;
	CVector		GetNormalAt		(CPoint3D pt);
	CColor		ShadePoint		(CIntersectionInfo hitInfo);
	CTexCoords	GetTexCoords	(CPoint3D ptOfIntersection){return CTexCoords(0,0);}	

	virtual ~CSphere();

protected:

	float m_fRadius;

};

# endif