// Point3D.cpp: implementation of the CPoint3D class.
//
//////////////////////////////////////////////////////////////////////

# include "Point3D.h"
# include <math.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPoint3D::CPoint3D()
{
	this->w = 1.0f;
}

CPoint3D::~CPoint3D()
{

}


/*********************************************************************
NAME       : CPoint3D
DESCRIPTION: Parameterized Constructor
PARAMETER  : x	: the value of the x coord
		     y	: the value of the y coord
			 z	: the value of the z coord
			 w	: the value of the w coord
RETURN     : NONE
EXCEPTION  : NONE.
*********************************************************************/

CPoint3D::CPoint3D(float x, float y, float z, float w)
{
	this->x = x;
	this->y = y;
	this->z = z;

	this->w = w;
}




/*********************************************************************
NAME       : SetPoint
DESCRIPTION: Set the value of the Coordinates
PARAMETER  : x	: the value of the x coord
		     y	: the value of the y coord
			 z	: the value of the z coord
RETURN     : NONE
EXCEPTION  : NONE.
*********************************************************************/

void CPoint3D::SetPoint (float x, float y, float z, float w)
{
	this->x = x;
	this->y = y;
	this->z = z;

	this->w = w;
}


/*********************************************************************
NAME       : AtInfinity
DESCRIPTION: Checks the w coord to see if the point lies at infinity 
             (for practical purposes, "is the point usable?")
PARAMETER  : NONE
RETURN     : bool
EXCEPTION  : NONE.
*********************************************************************/

bool CPoint3D::AtInfinity ()
{
	if(w == 0.0f)
	{
		return true;
	}
	
	return false;
}



/*********************************************************************
NAME       : IsCloser
DESCRIPTION: Returns true if it is closer to the reference point than
			 the given point. False otherwise.
PARAMETER  : ptOfReference	: The point to which both distances are
							  measured.
			 toCompare		: The point with which the distance has
							  to be compared.
RETURN     : bool
EXCEPTION  : NONE.
*********************************************************************/

bool CPoint3D::IsCloser (CPoint3D ptOfReference, CPoint3D toCompare)
{
	float thisDistance, thatDistance;

	if (this->AtInfinity() )
	{
		return false;
	}

	if (toCompare.AtInfinity() )
	{
		return true;
	}

	thisDistance = (ptOfReference.x - this->x) * (ptOfReference.x - this->x) + 
						(ptOfReference.y - this->y) * (ptOfReference.y - this->y) + 
							(ptOfReference.z - this->z) * (ptOfReference.z - this->z); 

	thatDistance = (ptOfReference.x - toCompare.x) * (ptOfReference.x - toCompare.x) + 
						(ptOfReference.y - toCompare.y) * (ptOfReference.y - toCompare.y) + 
							(ptOfReference.z - toCompare.z) * (ptOfReference.z - toCompare.z); 

	if (thisDistance < thatDistance || thatDistance <= 0.002)
	{
		return true;
	}

	return false;
}



/*********************************************************************
NAME       : GetX
DESCRIPTION: Gets the x coordinate of a the 3d Point.
PARAMETER  : NONE
RETURN     : float
EXCEPTION  : NONE.
*********************************************************************/

float CPoint3D::GetX () const
{
	return this->x;
}





/*********************************************************************
NAME       : GetX
DESCRIPTION: Gets the x coordinate of a the 3d Point.
PARAMETER  : NONE
RETURN     : float
EXCEPTION  : NONE.
*********************************************************************/

float CPoint3D::GetY () const
{
	return this->y;
}





/*********************************************************************
NAME       : GetZ
DESCRIPTION: Gets the z coordinate of a the 3d Point.
PARAMETER  : NONE
RETURN     : float
EXCEPTION  : NONE.
*********************************************************************/

float CPoint3D::GetZ () const
{
	return this->z;
}




/*********************************************************************
NAME       : GetW
DESCRIPTION: Gets the w coordinate of a the 3d Point.
PARAMETER  : NONE
RETURN     : float
EXCEPTION  : NONE.
*********************************************************************/

float CPoint3D::GetW () const
{
	return this->w;
}



/*********************************************************************
NAME       : operator-
DESCRIPTION: subtracts given point in space from this point and returns
the result
PARAMETER  : Point to be subtracted from this point.
RETURN     : CPoint3D: Resultant point
EXCEPTION  : NONE.
*********************************************************************/

CPoint3D CPoint3D::operator-(const CPoint3D& that)
{
	CPoint3D ptResultantPoint;
    
	ptResultantPoint.x = this->x - that.x;
	ptResultantPoint.y = this->y - that.y;
	ptResultantPoint.z = this->z - that.z;
    
	return ptResultantPoint;
}



/*********************************************************************
NAME       : operator+ (CVector)
DESCRIPTION: Creates a given vector to the point to get to a new position
			 in space
PARAMETER  : vecAdd	: the vector to add.
RETURN     : The resultant point in space.
EXCEPTION  : NONE.
*********************************************************************/

CPoint3D CPoint3D::operator+ (const CVector& vecAdd)
{
	CPoint3D result;
    
    result.x = x + vecAdd.XComponent();
    result.y = y + vecAdd.YComponent();
    result.z = z + vecAdd.ZComponent();
    
    return result;
}




/*********************************************************************
NAME       : GetDistance
DESCRIPTION: Finds the distance between two points
PARAMETER  : p1 : The first point
			 p2 : The second point
RETURN     : float	: the distance between the two points.
EXCEPTION  : NONE
*********************************************************************/

float CPoint3D::GetDistance	(CPoint3D p1, CPoint3D p2)
{
	float distanceSquared = (p2.x - p1.x) * (p2.x - p1.x) + 
								(p2.y - p1.y) * (p2.y - p1.y) + 
									(p2.z - p1.z) * (p2.z - p1.z);

	float distance = (float)sqrt (distanceSquared);

	return distance;
}
