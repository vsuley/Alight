// Sphere.cpp: implementation of the CSphere class.
//
//////////////////////////////////////////////////////////////////////

# include "Sphere.h"
# include "IntersectionInfo.h"

# include <Math.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSphere::CSphere()
{

}

CSphere::~CSphere()
{

}



/*********************************************************************
NAME       : CSphere
DESCRIPTION: Parameterized constructor
PARAMETER  : pos	: The position of the sphere in space.
		     col	: the color of the sphere
			 radius	: the radius of the sphere
RETURN     : NONE
EXCEPTION  : NONE.
*********************************************************************/

CSphere::CSphere(CPoint3D pos, CColor col, float radius) : CShape (pos, col)
{
	m_fRadius = radius;
}

	



/*********************************************************************
NAME       : CSphere
DESCRIPTION: Copy constructor
PARAMETER  : sphere1	: the object to be copied
RETURN     : NONE
EXCEPTION  : NONE.
*********************************************************************/

CSphere::CSphere(CSphere &sphere1)
{
	this->m_fRadius		= sphere1.m_fRadius;
	this->objColor		= sphere1.objColor;
	this->m_ptPosition	= sphere1.m_ptPosition;
}





/*********************************************************************
NAME       : SetRadius
DESCRIPTION: Sets the radius of the sphere
PARAMETER  : radius	: the new radius of the sphere
RETURN     : void
EXCEPTION  : NONE.
*********************************************************************/

void CSphere::SetRadius(float radius)
{
	m_fRadius = radius;
}






/*********************************************************************
NAME       : GetIntersection
DESCRIPTION: Calculates the intersection of the given ray with the sphere.
             If an intersection occurs the return value contains the 
			 homogenous coordinates of the point of intersection. If not,
			 then the 'w' of the homogenous coordinates returned is zero
PARAMETER  : ray	: the ray to test for.
RETURN     : 3D homogenous point
EXCEPTION  : NONE.
*********************************************************************/

CIntersectionInfo CSphere::GetIntersection (CRay ray)
{
	CPoint3D ptNoIntersection(0.0f,0.0f,0.0f,0.0f);	// no intersection by default
	CPoint3D ptOfIntersection;
	CIntersectionInfo hitInfo;
	
	float B;
	float C;
	float B2_4C;
	float omega;
	float fX, fY, fZ;
    
    // Default case:
    hitInfo.SetPointOfIntersection(ptNoIntersection);
	
	/******************************************************************************
	STRATEGY:

	To find the point of intersection, we will have to solve a quadratic equation. 
	The explanation of how this equation came about will soon be documented, for now
	the equation is solved in teh program.
	
	A quad eqn is of teh form : omega = ( -B +/- sqrt (B^2 - 4AC) ) / 2 A

	In this case, A is 1 because the direction of the ray is normalized.

	1. Calculate 'B'.
	2. Calculate 'C'
	3. Calculate the discriminator (ie B2 - 4AC)
	4. Make sure we don't have unreal roots
	5. Calculate Omega
	6. Make sure the point of intersection is in front of the ray.
	7. using omega, find the final point of intersection.
	8. Set values into the hitInfo object.
	9. Return the hitInfo object.
	******************************************************************************/

	// 1.
	B = 2.0f * ( ray.Direction().XComponent() * (ray.Origin().GetX() - m_ptPosition.GetX()) 
				
				+ ray.Direction().YComponent() * (ray.Origin().GetY() - m_ptPosition.GetY()) 
					
					+ ray.Direction().ZComponent() * (ray.Origin().GetZ() - m_ptPosition.GetZ()));

	
	// 2.
	C = (ray.Origin().GetX() - m_ptPosition.GetX()) * (ray.Origin().GetX() - m_ptPosition.GetX())

			+ (ray.Origin().GetY() - m_ptPosition.GetY()) * (ray.Origin().GetY() - m_ptPosition.GetY())

				+ (ray.Origin().GetZ() - m_ptPosition.GetZ()) * (ray.Origin().GetZ() - m_ptPosition.GetZ())
				
					- (m_fRadius * m_fRadius);

	
	// 3.
	B2_4C = B * B - 4 * C;

	// 4.
	if (B2_4C < 0)
	{
		// no real roots for quadratic equation.
		return hitInfo;
	}

	// 5.
	omega = (-B - (float)sqrt((double)B2_4C)) / 2;

	// 6.
	if(omega < 0)
	{
		// intersection is behind the origin, no use.
		return hitInfo;
	}

	// 7.
	fX = ray.Origin().GetX() + ray.Direction().XComponent() * omega;
	fY = ray.Origin().GetY() + ray.Direction().YComponent() * omega;
	fZ = ray.Origin().GetZ() + ray.Direction().ZComponent() * omega;
	
	ptOfIntersection.SetPoint(fX,fY,fZ);

	// 8. 
	hitInfo.SetPointOfIntersection (ptOfIntersection);
	hitInfo.SetColor (objColor);
	hitInfo.SetNormal (GetNormalAt(ptOfIntersection));
	hitInfo.SetTexCoords (GetTexCoords (ptOfIntersection));

	// 9.
	return hitInfo;
}



/*********************************************************************
NAME       : GetNormalAt
DESCRIPTION: Gets the normal at the specified point
PARAMETER  : pt	: the point
RETURN     : CVector
EXCEPTION  : NONE.
*********************************************************************/

CVector CSphere::GetNormalAt(CPoint3D pt)
{
	CVector vecNormal (pt - this->m_ptPosition);

	vecNormal.Normalize();

	return vecNormal;
}




/*********************************************************************
NAME       : ShadePoint
DESCRIPTION: This functin returns the color that should be displayed 
		     for this object given the hit details.
PARAMETER  : objHitInfo	:	detailed information about the hit.
RETURN     : NONE
EXCEPTION  : NONE.
*********************************************************************/

CColor CSphere::ShadePoint(CIntersectionInfo objHitInfo)
{
    if (m_pShader == 0)
		return this->objColor;
	
	return m_pShader->ShadePoint(objHitInfo);
}
