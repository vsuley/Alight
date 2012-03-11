// OnScreenObject.h: interface for the COnScreenObject class.
//
//////////////////////////////////////////////////////////////////////

# ifndef _ONSCREENOBJECT_H
# define _ONSCREENOBJECT_H


// The include files.
# include "Point3D.h"


class COnScreenObject  
{
public:
	
	// Constructors
	COnScreenObject		();
	COnScreenObject		(const COnScreenObject &obj1);
	COnScreenObject		(CPoint3D pos);
	
	// Interface
	void		SetPosition	(CPoint3D pos);
	CPoint3D	GetPosition	();

	// Destructor
	virtual ~COnScreenObject();

protected:
	CPoint3D	m_ptPosition;

};

# endif