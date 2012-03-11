// Environment.h: interface for the CEnvironment class.
//
//////////////////////////////////////////////////////////////////////

# ifndef _ENVIRONMENT_H
# define _ENVIRONMENT_H

#include "Shape.h"

class CEnvironment : public CShape  
{
public:
	// Object constructors
	CEnvironment(CPoint3D pos, CColor col);
	CEnvironment();
	
	// Destruction
	virtual ~CEnvironment();

	// Object interface
	CIntersectionInfo GetIntersection	(CRay ray);

	CVector		GetNormalAt		(CPoint3D pt);
	CColor		ShadePoint		(CIntersectionInfo objHitInfo);
	CTexCoords	GetTexCoords	(CPoint3D ptOfIntersection){return CTexCoords(0,0);}	
};

# endif