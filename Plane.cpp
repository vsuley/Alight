// Plane.cpp: implementation of the CPlane class.
//
//////////////////////////////////////////////////////////////////////

# include "Plane.h"
# include "IntersectionInfo.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPlane::CPlane()
{

}

CPlane::~CPlane()
{

}


/*********************************************************************
NAME       : CPlane
DESCRIPTION: Parameterized constructor
PARAMETER  : pos	: the position of the plane in space.
		     col	: the color of the plane.
			 width	: the width of hte plane
			 height	: the height of the plane.
			 normal	: the spatial orientation of the plane normal.
RETURN     : NONE
EXCEPTION  : NONE.
*********************************************************************/

CPlane::CPlane(CPoint3D pos, CColor col, float width, float length, CVector normal, CVector orientation) : CShape (pos, col)
{
	/************************************************************************
	NOTE:
	I have decided to define the plane in the following manner so that it is
	intuitive for the user to specify.
	a. The centre of the plane. 
	b. The normal of the plane.
	c. The height and the width of the plane.
	d. The tricky one - The orientation of the plane.

	Now, one might ask....isn't the normal the orientation? The answer is: if
	the plane is infinite, then yes, the normal is all the orientation you need.
	But if the plane is NOT infinite (which is the case here), we will have a
	plane-segment (or a rectangle), whose dimensions are length x width. 
	This rectangle can be rotated ABOUT THE NORMAL to face 	different directions. 
	but we have to pin one direction down, thus we specify an 'orientation'.

	The orientation, technically, is perfectly orthogonal to the normal, but 
	we cannot expect such a level of precision from the user. So, the user just
	gives us a vector that roughly defines the direction and we compute the 
	'perfect' orientation.

	We also need an 'ortho' vector which is orthogonal to both of these. This 
	vector helps simplify calculations later on when points on the plane have
	to be tested if they lie inside the rectangle.
	************************************************************************/

	/***********************************************************************
	STRATEGY:
	1. Copy width, length and Normal as they are.Normalize the normal vector.
	2. Get vector orthogonal to Normal along the orientation.
	3. Get the orthogonal vector.
	4. Compute 'F'.
	***********************************************************************/

	// 1.
	m_fWidth	= width;
	m_fLength	= length;
	m_vecNormal = normal;
	m_vecNormal.Normalize();

	// 2.
	m_vecOrientation = m_vecNormal.GetOrthoAlong (orientation);
	m_vecOrientation.Normalize();

	// 3.
	m_vecOrtho = m_vecOrientation.CrossProduct(m_vecNormal);
	m_vecOrtho.Normalize();

	// 4.
	m_fF = -1.0f * (m_vecNormal.XComponent() * m_ptPosition.GetX() + 
						m_vecNormal.YComponent() * m_ptPosition.GetY() + 
							m_vecNormal.ZComponent() * m_ptPosition.GetZ());
}



/*********************************************************************
NAME       : CPlane
DESCRIPTION: Copy constructor
PARAMETER  : plane1	: the object to copy
RETURN     : NONE
EXCEPTION  : NONE.
*********************************************************************/

CPlane::CPlane(CPlane &plane1)
{
	this->m_fF			   = plane1.m_fF;
	this->m_fLength		   = plane1.m_fLength;
	this->m_fWidth		   = plane1.m_fWidth;
	this->m_pShader		   = plane1.m_pShader;
	this->m_ptPosition	   = plane1.m_ptPosition;
	this->m_vecNormal	   = plane1.m_vecNormal;
	this->m_vecOrientation = plane1.m_vecOrientation;
	this->m_vecOrtho	   = plane1.m_vecOrtho;
	this->objColor		   = plane1.objColor;
}





/*********************************************************************
NAME       : SetDimensions	
DESCRIPTION: Sets teh length and width of the plane.
PARAMETER  : width, length
RETURN     : void
EXCEPTION  : NONE.
*********************************************************************/

void CPlane::SetDimensions	(float width, float length)
{
	this->m_fWidth	= width;
	this->m_fLength = length;
}

	

/*********************************************************************
NAME       : SetNormal
DESCRIPTION: Set the normal
PARAMETER  : normal	: the value to use
RETURN     : void
EXCEPTION  : NONE.
*********************************************************************/

void CPlane::SetNormal		(CVector normal)
{
	this->m_vecNormal = normal;

	m_vecNormal.Normalize();
}
	

/*********************************************************************
NAME       : GetNormalAt	
DESCRIPTION: returns the plane normal
PARAMETER  : pt	:	ignored
RETURN     : vector denoting the normal
EXCEPTION  : NONE.
*********************************************************************/

CVector CPlane::GetNormalAt	(CPoint3D pt)
{
	return this->m_vecNormal;
}



/*********************************************************************
NAME       : GetIntersection
DESCRIPTION: Calculates the intersection of the given ray with the plane.
             If an intersection occurs the return value contains the 
			 homogenous coordinates of the point of intersection. If not,
			 then the 'w' of the homogenous coordinates returned is zero
PARAMETER  : ray	: the ray to test for.
RETURN     : 3D homogenous point
EXCEPTION  : NONE.
*********************************************************************/

CIntersectionInfo CPlane::GetIntersection	(CRay ray)
{
	CPoint3D ptNoIntersection (0.0f, 0.0f, 0.0f, 0.0f);	// no intersection by default
	CPoint3D ptOfIntersection;
	CIntersectionInfo hitInfo;

	float fX, fY, fZ;

	CVector vecPn, vecD;
	float omega, fPndotD;


	/****************************************************************************
	STRATEGY:

	The equation we use is:
	omega = - ( Pn.P0 + F) / (Pn.D)
	
	1. First find the point of intersection of ray with INFINITE PLANE containing 
	   this plane so that it lies in front of the ray origin.
	2. Now see if the point of intersection lies inside OUR PLANE. 
	3. Ready the hitInfo object so that we can return it.
	****************************************************************************/
	
	// 1.
		/*********************************************************************
		STRATEGY:
		1.1. Compute Pn.D
		1.2. If the ray is parallel to the plane, return.
		1.3. Compute F
		1.4. Compute Omega
		1.5. If the pt is behind us, return.
		1.6. Compute the coordinates of the point.
		*********************************************************************/
		
		// 1.1.
		fPndotD = m_vecNormal.DotProduct(ray.Direction());
		
		// 1.2.
		if (!fPndotD)
		{
			return hitInfo;
		}

		// 1.3.
		
		// 1.4.
		omega = - (m_vecNormal.DotProduct(ray.Origin()) + m_fF) / fPndotD;

		// 1.5.
		if (omega < 0)
		{
			return hitInfo;
		}

		// 1.6.
		fX = ray.Origin().GetX() + ray.Direction().XComponent() * omega;
		fY = ray.Origin().GetY() + ray.Direction().YComponent() * omega;
		fZ = ray.Origin().GetZ() + ray.Direction().ZComponent() * omega;


	// 2.
	float localX, localY;
	CVector vecLocalPos = CVector(fX, fY, fZ) - CVector (m_ptPosition);

	localX = m_vecOrtho.DotProduct(vecLocalPos);
	localY = m_vecOrientation.DotProduct (vecLocalPos);

	if (localY < (-1.0f * 0.5 * m_fLength) || localY > 0.5 * m_fLength ||
			localX < (-1.0f * 0.5 * m_fWidth) || localX > 0.5 * m_fWidth)
	{
		return hitInfo;
	}
	
	
	ptOfIntersection.SetPoint(fX,fY,fZ);

	// 3.
	hitInfo.SetPointOfIntersection(ptOfIntersection);
	hitInfo.SetNormal(m_vecNormal);
	hitInfo.SetColor (objColor);
	hitInfo.SetTexCoords(GetTexCoords (ptOfIntersection));

	return hitInfo;
}




/*********************************************************************
NAME       : ShadePoint
DESCRIPTION: This functin returns the color that should be displayed 
		     for this object given the hit details.
PARAMETER  : objHitInfo	:	detailed information about the hit.
RETURN     : NONE
EXCEPTION  : NONE.
*********************************************************************/

CColor CPlane::ShadePoint(CIntersectionInfo objHitInfo)
{
	if (m_pShader == 0)
		return this->objColor;
	
	return m_pShader->ShadePoint(objHitInfo);
}



/*********************************************************************
NAME       : GetTexCoords
DESCRIPTION: This method returns the texture coordinates for the given
		     point on the surface of the object.
PARAMETER  : ptOfIntersection	: The point at which tex coords have to
								  be computed.
RETURN     : CTexCoords.
EXCEPTION  : NONE.
*********************************************************************/

CTexCoords	CPlane::GetTexCoords	(CPoint3D ptOfIntersection)
{
	CVector vecCorner, a;
	float u,v;

	vecCorner = CVector(m_ptPosition) - (m_vecOrtho * 0.5f * m_fWidth) - (m_vecOrientation * 0.5f * m_fLength);

	a = CVector(ptOfIntersection) - vecCorner;

	u = (m_vecOrtho.DotProduct (a)) / m_fWidth;
	v = (m_vecOrientation.DotProduct(a)) / m_fLength;

	return CTexCoords (u,v);
}
