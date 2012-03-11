// Triangle.cpp: implementation of the CTriangle class.
//
//////////////////////////////////////////////////////////////////////

# include "Triangle.h"
# include "IntersectionInfo.h"
# include "GlobalConstants.h"
# include "math.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTriangle::CTriangle()
{

}

CTriangle::~CTriangle()
{
    // Write code to prevent memory leaks.
}


/*********************************************************************
NAME       : CTriangle
DESCRIPTION: Parameterized constructor. Use only for Vertex Normal mode.
PARAMETER  : pos	: the position of the plane in space.
		     col	: the color of the plane.
			 pptVertices : an array of the triangle vertices.
			 normals: One normal for each vertex of the triangle
RETURN     : NONE
EXCEPTION  : NONE.
*********************************************************************/

CTriangle::CTriangle	(CPoint3D pos, CColor col, CPoint3D pptVertices[3], CVector pvecNormals[3]) : CShape (pos, col)
{
	m_pptVertices[0] = pptVertices[0];
	m_pptVertices[1] = pptVertices[1];
	m_pptVertices[2] = pptVertices[2];

	m_pvecNormals[0] = pvecNormals[0];
	m_pvecNormals[0].Normalize();

	m_pvecNormals[1] = pvecNormals[1];
	m_pvecNormals[1].Normalize();

	m_pvecNormals[2] = pvecNormals[2];
	m_pvecNormals[2].Normalize();

	m_eNormalMode = VERTEX_NORMAL;

	m_pShader = 0;
}


/*********************************************************************
NAME       : CTriangle
DESCRIPTION: Parameterized constructor. Use only for Face normal mode.
PARAMETER  : pos	: the position of the plane in space.
		     col	: the color of the plane.
			 pptVertices : an array of the triangle vertices.
			 normal	: the spatial orientation of the traingle.
RETURN     : NONE
EXCEPTION  : NONE.
*********************************************************************/

CTriangle::CTriangle	(CPoint3D pos, CColor col, CPoint3D pptVertices[3]) : CShape (pos, col)
{
	m_pptVertices[0] = pptVertices[0];
	m_pptVertices[1] = pptVertices[1];
	m_pptVertices[2] = pptVertices[2];

	m_eNormalMode = FACE_NORMAL;
	
	// VVIMP - do not forget this step!
	ComputeFaceNormal();
	
	m_pShader = 0;
}

/*********************************************************************
NAME       : CTriangle
DESCRIPTION: Copy constructor
PARAMETER  : plane1	: the object to copy
RETURN     : NONE
EXCEPTION  : NONE.
*********************************************************************/

CTriangle::CTriangle	(CTriangle &triangle1)
{
	this->m_eNormalMode = triangle1.m_eNormalMode;


	if (m_eNormalMode == FACE_NORMAL) {
		
		this->m_vecNormal = triangle1.m_vecNormal;
	}
	else {
		
		this->m_pvecNormals[0] = triangle1.m_pvecNormals[0];
		this->m_pvecNormals[1] = triangle1.m_pvecNormals[1];
		this->m_pvecNormals[2] = triangle1.m_pvecNormals[2];
	}
	
	this->m_pptVertices[0] = triangle1.m_pptVertices[0];
	this->m_pptVertices[1] = triangle1.m_pptVertices[1];
	this->m_pptVertices[2] = triangle1.m_pptVertices[2];
	
	
	this->m_pShader		= triangle1.m_pShader;
	this->m_ptPosition	= triangle1.m_ptPosition;
	this->objColor		= triangle1.objColor;
}



/*********************************************************************
NAME       : Init
DESCRIPTION: Object initializer
PARAMETER  :    pos	: the position of the plane in space.
                col	: the color of the plane.
                pptVertices : an array of the triangle vertices.
                normals: One normal for each vertex of the triangle
RETURN     : void
EXCEPTION  : NONE.
*********************************************************************/

void CTriangle::Init (CPoint3D pos, CColor col, CPoint3D pptVertices[3], CVector pvecNormals[3])
{
    objColor = col;
    m_ptPosition = pos;
    
	m_pptVertices[0] = pptVertices[0];
	m_pptVertices[1] = pptVertices[1];
	m_pptVertices[2] = pptVertices[2];
    
	m_pvecNormals[0] = pvecNormals[0];
	m_pvecNormals[0].Normalize();
    
	m_pvecNormals[1] = pvecNormals[1];
	m_pvecNormals[1].Normalize();
    
	m_pvecNormals[2] = pvecNormals[2];
	m_pvecNormals[2].Normalize();
    
	m_eNormalMode = VERTEX_NORMAL;
    
	m_pShader = 0;
} 


/*********************************************************************
NAME       : Init
DESCRIPTION: Object initializer
PARAMETER  :    pos	: the position of the plane in space.
                col	: the color of the plane.
                pptVertices : an array of the triangle vertices.
RETURN     : void
EXCEPTION  : NONE.
*********************************************************************/

void CTriangle::Init (CPoint3D pos, CColor col, CPoint3D pptVertices[3])
{
    objColor = col;
    m_ptPosition = pos;
    
	m_pptVertices[0] = pptVertices[0];
	m_pptVertices[1] = pptVertices[1];
	m_pptVertices[2] = pptVertices[2];
   
	m_eNormalMode = FACE_NORMAL;
	
	// VVIMP - do not forget this step!
	ComputeFaceNormal();
    
	m_pShader = 0;
}



// Object interface
/*********************************************************************
NAME       : GetNormalAt	
DESCRIPTION: returns the plane normal
PARAMETER  : pt	:	ignored
RETURN     : vector denoting the normal
EXCEPTION  : NONE.
*********************************************************************/

CVector	CTriangle::GetNormalAt(CPoint3D pt)
{
	// Temporary
	return m_vecNormal;
}



/*********************************************************************
NAME       : GetIntersection
DESCRIPTION: Calculates the intersection of the given ray with the triangle.
             If an intersection occurs the return value contains the 
			 homogenous coordinates of the point of intersection. If not,
			 then the 'w' of the homogenous coordinates returned is zero
PARAMETER  : ray	: the ray to test for.
RETURN     : 3D homogenous point
EXCEPTION  : NONE.
*********************************************************************/

CIntersectionInfo CTriangle::GetIntersection	(CRay ray)
{
	CPoint3D ptNoIntersection (0.0f, 0.0f, 0.0f, 0.0f);	// no intersection by default
	CPoint3D ptOfIntersection;
	CIntersectionInfo hitInfo;

	/***************************************************************
	STRATEGY:

	There are two major steps when trying to find the point of 
	intersection of a ray with a triangle, first to see if the ray
	intersects the plane of the triangle and then to see if the point
	on the plane that the ray intersects with lies within the triangle.

	So:
	1. Find the point of intersection on the triangle plane.
	2. Check if this point lies insdie the plane or not.
	3. Set the information into the hitInfo object.
	4. Return the hitInfo object.
	***************************************************************/

	// 1.
	ptOfIntersection = PlaneIntersect(ray);

	// 2.
	if ( !inTriangle(ptOfIntersection) || ptOfIntersection.AtInfinity()) {

		return hitInfo;
	}

	// 3.
	hitInfo.SetPointOfIntersection (ptOfIntersection);
	hitInfo.SetNormal (GetNormalAt(ptOfIntersection));
	hitInfo.SetColor(objColor);
	hitInfo.SetTexCoords (GetTexCoords(ptOfIntersection));

	// 4.
	return hitInfo;
}





/*********************************************************************
NAME       : PlaneIntersect		
DESCRIPTION: Calculates the point of intersection of they ray with the 
		     plane containing the triangle.
PARAMETER  : ray	: the ray to test for.
RETURN     : 3D homogenous point
EXCEPTION  : NONE.
*********************************************************************/

CPoint3D CTriangle::PlaneIntersect		(CRay ray)
{
	CPoint3D ptOfIntersection;

	float D, t;

	/***************************************************************
	STRATEGY:
	
	The equation of a plane is of hte form ; Ax + By + Cz + D = 0. 
	A, B and C come from the normal which we already have, now we 
	have to compute D. After that we can start testing for intersection.

	1. Find the factor D to complete our equation of the plane.
	2. Find the value of t. given by:
		t = - (AX0 + BY0 + CY0 + D) / (A delX + B delY + C delZ)
	   where X0.... are the origin of the ray and delX ....are the 
	   diff between start and end point of the ray. If the ray is 
	   normalized then t gives the distance from the origin of the ray.
	3. If t is negative, triangle is behind, else multiply t to the ray
	   to get the absolute coords of the point of intersection.
	***************************************************************/

	// 1.
	D = -1.0f * (m_vecNormal.XComponent() * m_pptVertices[0].GetX() + 
					m_vecNormal.YComponent() * m_pptVertices[0].GetY() + 
						m_vecNormal.ZComponent() * m_pptVertices[0].GetZ());

	// 2.
		
		float numer, denom;
		/************************************************************
		2.1. Compute the denominator first. If it is zero, no intersection.
		2.2. Compute the numerator.
		2.3. Divide and negate to get t.
		************************************************************/
		
		// 2.1.
		denom = m_vecNormal.XComponent() * ray.Direction().XComponent() + 
					m_vecNormal.YComponent() * ray.Direction().YComponent() + 
						m_vecNormal.ZComponent() * ray.Direction().ZComponent();
		
		if (denom <= 0.0f + MARGIN_OF_ERROR && denom >= 0.0f - MARGIN_OF_ERROR) {

			return CPoint3D (0,0,0,0); // infinity
		}

		// 2.2.
		numer = m_vecNormal.XComponent() * ray.Origin().GetX() + 
					m_vecNormal.YComponent() * ray.Origin().GetY() + 
						m_vecNormal.ZComponent() * ray.Origin().GetZ() + D;

		// 2.3.
		t = -1.0f * numer / denom;

	
		
	// 3.
	if (t < 0) {
		
		return CPoint3D (0,0,0,0); // behind us; return infinity
	}

	ptOfIntersection = ray.Origin() + (ray.Direction() * t);

	return ptOfIntersection;

}


/*********************************************************************
NAME       : inTriangle
DESCRIPTION: This function checks to see if a certain point is within
			 this triangle using Barycentric coordinates.
PARAMETER  : ptOfIntersection	: The point to test for containment.
RETURN     : bool	: True if contained, false otherwise
EXCEPTION  : NONE.
*********************************************************************/

bool	 CTriangle::inTriangle			(CPoint3D ptOfIntersection)
{
	/****************************************************************
	NOTE:
	This is an expensive but easy to implement approach for testing 
	if a point lies within a triangle.

	The idea is to join each of the vertices with the point in question.
	
	Taking the point and two out of three vertices each time, we get 
	three more triangles. It is easy to see that if this point is within
	the triangle boundary then the three triangles fit in completely
	inside the bigger one.

	Thus, if the sum of the areas of the three sub-triangles is equal
	to the area of the larger triangle, the point is within the triangle.
	****************************************************************/
	// yet another approach.

	float area, subArea1, subArea2, subArea3;

	CVector side1, side2;

	side1 = CVector (m_pptVertices[1] - m_pptVertices[0]);
	side2 = CVector (m_pptVertices[2] - m_pptVertices[0]);

	area = 0.5f * (side1.CrossProduct(side2)).Magnitude();
	
	CVector s1, s2;
	
	// subArea1.
	s1 = CVector (ptOfIntersection - m_pptVertices[0]);
	s2 = CVector (m_pptVertices[1] - m_pptVertices[0]);
	
	subArea1 = 0.5f * s1.CrossProduct(s2).Magnitude();

	// subArea2
	s1 = CVector (ptOfIntersection - m_pptVertices[1]);
	s2 = CVector (m_pptVertices[2] - m_pptVertices[1]);
	
	subArea2 = 0.5f * s1.CrossProduct(s2).Magnitude();

	// subArea3
	s1 = CVector (ptOfIntersection - m_pptVertices[2]);
	s2 = CVector (m_pptVertices[0] - m_pptVertices[2]);
	
	subArea3 = 0.5f * s1.CrossProduct(s2).Magnitude();

	float total = subArea1 + subArea2 + subArea3;

	if(total <= area + 0.1 && total >= area - 0.1) {

		return true;
	}

	return false;
}



/*********************************************************************
NAME       : ShadePoint
DESCRIPTION: This functin returns the color that should be displayed 
		     for this object given the hit details.
PARAMETER  : objHitInfo	:	detailed information about the hit.
RETURN     : NONE
EXCEPTION  : NONE.
*********************************************************************/

CColor CTriangle::ShadePoint(CIntersectionInfo objHitInfo)
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

CTexCoords	CTriangle::GetTexCoords	(CPoint3D ptOfIntersection)
{
	return CTexCoords (0,0);
}




/*********************************************************************
NAME       : ComputeFaceNormal
DESCRIPTION: This method computes the face normal of the triangle
PARAMETER  : NONE
RETURN     : void.
EXCEPTION  : NONE.
*********************************************************************/

void CTriangle::ComputeFaceNormal()
{
	// Counterclockwise winding.
	// vec1= vert0 - vert1
	// vec2= vert2 - vert1
	// normal  = vec2 x vec1

	CVector vecOne, vecTwo;

	vecOne = CVector (m_pptVertices[0]) - CVector(m_pptVertices[1]);

	vecTwo = CVector (m_pptVertices[2]) - CVector(m_pptVertices[1]);

	
	m_vecNormal = vecTwo.CrossProduct (vecOne);
	m_vecNormal.Normalize();
	m_vecNormal = m_vecNormal;// * -1.0f;
}
