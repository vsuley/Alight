// Plane.h: interface for the CPlane class.
//
//////////////////////////////////////////////////////////////////////

# ifndef _PLANE_H
# define _PLANE_H


// Include files
# include "Shape.h"
# include "Vector.h"

class CPlane : public CShape  
{
public:
	
	// Object constructors
	CPlane();
	CPlane(CPoint3D pos, CColor col, float width, float height, CVector normal, CVector orientation);
	CPlane(CPlane &plane1);

	// Object interface
	CIntersectionInfo	GetIntersection	(CRay ray);

	void		SetDimensions	(float width, float height);
	CVector		GetNormalAt		(CPoint3D pt);
	void		SetNormal		(CVector normal);
	CColor		ShadePoint		(CIntersectionInfo hitInfo);
	CTexCoords	GetTexCoords	(CPoint3D ptOfIntersection);
	
	// Destruction
	virtual ~CPlane();

protected:
	
	float		m_fWidth;
	float		m_fLength;
	
	// The following three vectors form a orthogonal coordinate
	// system of their own. See 'note' in constructor
	CVector		m_vecNormal;
	CVector		m_vecOrientation;
	CVector		m_vecOrtho;

	float		m_fF;
};

# endif