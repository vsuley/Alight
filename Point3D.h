// Point3D.h: interface for the CPoint3D class.
//
//////////////////////////////////////////////////////////////////////

# ifndef _POINT3D_H
# define _POINT3D_H

# include "Vector.h"

class CPoint3D  
{
public:
	// Object Construction
	CPoint3D();
	CPoint3D(float x, float y, float z, float w = 1.0);

	// Object interface
	void	SetPoint	(float x, float y, float z, float w = 1.0);
	bool	AtInfinity	();
	bool	IsCloser	(CPoint3D ptOfReference, CPoint3D toCompare);
	float	GetX() const;
	float	GetY() const;
	float	GetZ() const;
    float   GetW() const;
	
	// utility functions of class
	float	static GetDistance	(CPoint3D p1, CPoint3D p2);

	// Object operators
	CPoint3D operator- (const CPoint3D& pt);
	CPoint3D operator+ (const CVector& vecAdd);
	
	// Object destruction
	virtual ~CPoint3D();

protected:

	float x; 
	float y;
	float z;
	float w;
};

# endif _POINT3D_H