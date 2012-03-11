// Light.h: interface for the CLight class.
//
//////////////////////////////////////////////////////////////////////

# ifndef _LIGHT_H
# define _LIGHT_H

# include "OnScreenObject.h"
# include "Color.h"
# include "Point3D.h"

class CLight  : public COnScreenObject
{
public:
	
	// Object construction
	CLight();
	CLight(CColor color, float intensity, CPoint3D ptPosition);
	CLight(CLight &l1);

	// Object deconstruction.
	virtual ~CLight();

	// Object interface.
	CColor	GetColor		();
	float	GetIntensity	();


protected:
	CColor		m_colLight;
	float		m_fIntensity;
};

# endif