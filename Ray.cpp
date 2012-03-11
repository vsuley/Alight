// Ray.cpp: implementation of the CRay class.
//
//////////////////////////////////////////////////////////////////////

#include "Ray.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CRay::CRay()
{

}

CRay::~CRay()
{

}




/*********************************************************************
NAME       : CRay
DESCRIPTION: Parameterized constructor
PARAMETER  : ptOrigin		: The point in 3D space where the ray 
							  originates
			 ptDestination	: The point where the ray ends
RETURN     : NONE
EXCEPTION  : NONE.
*********************************************************************/

CRay::CRay(CPoint3D ptOrigin, CPoint3D ptDestination, float IOR)
{
	m_ptOrigin		= ptOrigin;

	m_ptDestination = ptDestination;

	m_vecDirection	= ptDestination - ptOrigin;

	m_fMagnitude	= m_vecDirection.Magnitude();

	m_fIndexOfRefraction = IOR;
	
    m_vecDirection.Normalize();
}




/*********************************************************************
NAME       : CRay
DESCRIPTION: Overloaded constructor....creates a ray object given a 
			 vector
PARAMETER  : vec	: The vector to construct the ray from
RETURN     : NONE
EXCEPTION  : NONE.
*********************************************************************/

CRay::CRay(CVector& vec)
{
	m_ptOrigin		= CPoint3D (0.0f, 0.0f, 0.0f);
	m_ptDestination = CPoint3D (vec.XComponent(), vec.YComponent(), vec.ZComponent());
	m_vecDirection	= vec;
	m_fMagnitude	= vec.Magnitude();
	
	
	/******************************************************/
	// Do something about this real soon!
	m_fIndexOfRefraction = 1;
	/******************************************************/
	
	m_vecDirection.Normalize();
}



/*********************************************************************
NAME       : CRay
DESCRIPTION: Overloaded constructor....creates a ray object given a 
vector
PARAMETER  : vec	: The vector to construct the ray from
RETURN     : NONE
EXCEPTION  : NONE.
*********************************************************************/

CRay& CRay:: operator=(const CVector& vec)
{
    m_ptOrigin		= CPoint3D (0.0f, 0.0f, 0.0f);
	m_ptDestination = CPoint3D (vec.XComponent(), vec.YComponent(), vec.ZComponent());
	m_vecDirection	= vec;
	m_fMagnitude	= vec.Magnitude();
	
	
	/******************************************************/
	// Do something about this real soon!
	m_fIndexOfRefraction = 1;
	/******************************************************/
	
	m_vecDirection.Normalize();
    
    return *this;
}


/*********************************************************************
NAME       : Origin
DESCRIPTION: Gets the CPoint3D object denoting the origin of the ray.
PARAMETER  : NONE.
RETURN     : CPoint3D object containing the origin
EXCEPTION  : NONE.
*********************************************************************/

CPoint3D	CRay::Origin		()
{
	return m_ptOrigin;
}



/*********************************************************************
NAME       : Destination
DESCRIPTION: Gets the CPoint3D object denoting the end point of the ray.
PARAMETER  : NONE.
RETURN     : CPoint3D object containing the ending point
EXCEPTION  : NONE.
*********************************************************************/

CPoint3D	CRay::Destination()
{
	return m_ptDestination;
}


/*********************************************************************
NAME       : Direction
DESCRIPTION: Returns the CVector object containing the direction of 
			 the ray.
PARAMETER  : NONe
RETURN     : The CVector object containing the direction
EXCEPTION  : NONE.
*********************************************************************/

CVector		CRay::Direction	()
{
	return m_vecDirection;
}





/*********************************************************************
NAME       : Magnitude
DESCRIPTION: returns the Magnitude of the ray.
PARAMETER  : NONE
RETURN     : The magnitude in floating point
EXCEPTION  : NONE.
*********************************************************************/

float		CRay::Magnitude	()
{
	return m_fMagnitude;
}




/*********************************************************************
NAME       : IOR
DESCRIPTION: Returns the index of refraction of the medium the ray 
			 is travelling inside.
PARAMETER  : NONE
RETURN     : float :	The index of refraction.
EXCEPTION  : NONE.
*********************************************************************/

float CRay::IOR()
{
	return m_fIndexOfRefraction;
}



/*********************************************************************
NAME       : Translate
DESCRIPTION: Translates teh ray by the given point.
PARAMETER  : point
RETURN     : void
EXCEPTION  : NONE.
*********************************************************************/

void CRay::Translate	(CPoint3D point)
{
	m_ptOrigin		= m_ptOrigin + point;
	m_ptDestination = m_ptDestination + point;
}


