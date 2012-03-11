// Environment.cpp: implementation of the CEnvironment class.
//
//////////////////////////////////////////////////////////////////////

# include "Environment.h"
# include "IntersectionInfo.h"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CEnvironment::CEnvironment()
{

}

CEnvironment::~CEnvironment()
{

}



/*********************************************************************
NAME       : CEnvironment
DESCRIPTION: Parameterized constructor
PARAMETER  : pos	: Ignored
		     col	: the color of the plane.
RETURN     : NONE
EXCEPTION  : NONE.
*********************************************************************/

CEnvironment::CEnvironment(CPoint3D pos, CColor col) : CShape(pos,col)
{
}


/*********************************************************************
NAME       : GetIntersection
DESCRIPTION: This does not make much difference in case of the enivronment
			 this function simply returns a point at infinity.
PARAMETER  : ray	: Ignored.
RETURN     : NONE
EXCEPTION  : NONE.
*********************************************************************/

CIntersectionInfo CEnvironment::GetIntersection	(CRay ray)
{
	return CIntersectionInfo();
}


/*********************************************************************
NAME       : GetNormalAt
DESCRIPTION: This does not make much sense in case of environement. Just
			 returns an empty vector.
PARAMETER  : pt	: Ignored.
RETURN     : NONE
EXCEPTION  : NONE.
*********************************************************************/

CVector CEnvironment::GetNormalAt(CPoint3D pt)
{
	return CVector();
}


/*********************************************************************
NAME       : ShadePoint
DESCRIPTION: This functin returns the color that should be displayed 
		     for this object given the hit details.
PARAMETER  : objHitInfo	:	detailed information about the hit.
RETURN     : NONE
EXCEPTION  : NONE.
*********************************************************************/

CColor CEnvironment::ShadePoint(CIntersectionInfo objHitInfo)
{
	return objColor;
}