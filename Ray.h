// Ray.h: interface for the CRay class.
//
//////////////////////////////////////////////////////////////////////

# ifndef _RAY_H
# define _RAY_H


# include "Vector.h"
# include "Point3D.h"

class CRay  
{
public:

	// Object construction
	CRay	();
	CRay	(CPoint3D ptOrigin, CPoint3D ptDestination, float IOR);
	CRay	(CVector& vec);
    
    // Object assignment
    CRay& operator= (const CVector& vec);
	
	// Object destruction
	virtual ~CRay();

	// Object interface
	CPoint3D	Origin		();
	CPoint3D	Destination ();
	CVector		Direction	();
	float		Magnitude	();
	void		Translate	(CPoint3D point);
	float		IOR			();

protected:
	CPoint3D	m_ptOrigin;
	CPoint3D	m_ptDestination;
	CVector		m_vecDirection;
	float		m_fMagnitude;
	float		m_fIndexOfRefraction;

};


# endif