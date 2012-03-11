// Light.cpp: implementation of the CLight class.
//
//////////////////////////////////////////////////////////////////////

#include "Light.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLight::CLight()
{

}




/*********************************************************************
NAME       : CLight
DESCRIPTION: Parametrized constructor
PARAMETER  : color		: The color of the light
			 intensity	: The brightness of the light.
			 ptPosition	: The position of the light in space.

RETURN     : NONE
EXCEPTION  : NONE.
*********************************************************************/

CLight::CLight(CColor color, float intensity, CPoint3D ptPosition) : COnScreenObject(ptPosition)
{
	this->m_colLight	= color;
	this->m_fIntensity	= intensity;
}


/*********************************************************************
NAME       : CLight
DESCRIPTION: Copy constructor
PARAMETER  : l1	: The light object to copy.
RETURN     : NONE
EXCEPTION  : NONE.
*********************************************************************/

CLight::CLight(CLight &l1) : COnScreenObject((COnScreenObject)l1)
{
	this->m_colLight	= l1.m_colLight;
	this->m_fIntensity	= l1.m_fIntensity;
}

CLight::~CLight()
{

}



/*********************************************************************
NAME       : GetColor
DESCRIPTION: Retrieve the color of the light
PARAMETER  : NONE
RETURN     : CColor
EXCEPTION  : NONE.
*********************************************************************/

CColor	CLight::GetColor		()
{
	return this->m_colLight;
}


/*********************************************************************
NAME       : GetIntensity
DESCRIPTION: Retrieve the intensity of the light
PARAMETER  : NONE
RETURN     : float
EXCEPTION  : NONE.
*********************************************************************/

float	CLight::GetIntensity	()
{
	return m_fIntensity;
}
