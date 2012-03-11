// IntersectionInfo.cpp: implementation of the CIntersectionInfo class.
//
//////////////////////////////////////////////////////////////////////

#include "IntersectionInfo.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CIntersectionInfo::CIntersectionInfo() : m_vecNormal(0,0,0), m_vecIncoming(0,0,0)
{
	m_colObject		= CColor (0,0,0);
	m_ptIntersection= CPoint3D (0,0,0);
	m_pShapeObject	= 0;
	m_texIntersection	= CTexCoords(0,0);
	m_eIntersectionType=ENTRY;
}



/*********************************************************************
NAME       : CIntersectionInfo
DESCRIPTION: Copy constructor
PARAMETER  : obj1	: The object to copy
RETURN     : NONE
EXCEPTION  : NONE.
*********************************************************************/

CIntersectionInfo::CIntersectionInfo(const CIntersectionInfo& obj1) : 	m_vecNormal(obj1.m_vecNormal), m_vecIncoming(obj1.m_vecIncoming)
{
	m_colObject		= obj1.m_colObject;
	m_ptIntersection	= obj1.m_ptIntersection;
	m_pShapeObject	= obj1.m_pShapeObject;
	m_texIntersection	= obj1.m_texIntersection;
	m_eIntersectionType=obj1.m_eIntersectionType;
}


/*********************************************************************
NAME       : operator =
DESCRIPTION: Assignment operator
PARAMETER  : obj1	: The object to copy
RETURN     : NONE
EXCEPTION  : NONE.
*********************************************************************/

CIntersectionInfo& CIntersectionInfo::operator= (const CIntersectionInfo& that)
{
    if(this != &that)
    {
        m_vecNormal     = that.m_vecNormal;
        m_vecIncoming   = that.m_vecIncoming;
        m_colObject		= that.m_colObject;
        m_texIntersection	= that.m_texIntersection;
        m_eIntersectionType = that.m_eIntersectionType;
        m_ptIntersection	= that.m_ptIntersection;
        
        // FLAG FLAG FLAG - Potential memory leak here. Think about what to do here.
        m_pShapeObject      = that.m_pShapeObject;
    }
    
    return *this;
}


/*********************************************************************
NAME       : CIntersectionInfo
DESCRIPTION: Parameterized constructor
PARAMETER  : pt		:	The point of intersection
			 normal	:	The normal at the point of intersection
			 col	:	The object color at the point of intersection.
RETURN     : NONE
EXCEPTION  : NONE.
*********************************************************************/

CIntersectionInfo::CIntersectionInfo(CPoint3D pt, CVector normal, CColor col, CShape* pShape, CVector vecIncoming, CTexCoords texIntersection, EIntersectionType eType)
{
	this->m_colObject		= col;
	this->m_ptIntersection	= pt;
	this->m_vecNormal		= normal;
	this->m_pShapeObject	= pShape;
	this->m_vecIncoming		= vecIncoming;
	this->m_texIntersection	= texIntersection;
	this->m_eIntersectionType=eType;
}




/*********************************************************************
NAME       : GetNormal
DESCRIPTION: Returns the normal at the point of intersection
PARAMETER  : NONE
RETURN     : CNormal
EXCEPTION  : NONE.
*********************************************************************/

CVector CIntersectionInfo::	GetNormal()
{
	return this->m_vecNormal;
}



/*********************************************************************
NAME       : GetColor
DESCRIPTION: Returns the color at the point of intersection
PARAMETER  : NONE
RETURN     : CColor
EXCEPTION  : NONE.
*********************************************************************/

CColor CIntersectionInfo::GetColor()
{
	return this->m_colObject;
}



/*********************************************************************
NAME       : GetPointOfIntersection
DESCRIPTION: Returns the point of intersection
PARAMETER  : NONE
RETURN     : CPoint3D
EXCEPTION  : NONE.
*********************************************************************/

CPoint3D CIntersectionInfo::GetPointOfIntersection()
{
	return this->m_ptIntersection;
}





/*********************************************************************
NAME       : GetTextureCoordinates
DESCRIPTION: Returns the texture coordinates at the point of intersection
PARAMETER  : NONE
RETURN     : CTexCoords
EXCEPTION  : NONE.
*********************************************************************/

CTexCoords CIntersectionInfo::GetTextureCoordinates()
{
	return this->m_texIntersection;
}



/*********************************************************************
NAME       : GetShape
DESCRIPTION: Returns the shape that the intersection happened with
PARAMETER  : NONE
RETURN     : CShape*
EXCEPTION  : NONE.
*********************************************************************/

CShape* CIntersectionInfo::GetShape()
{
	return this->m_pShapeObject;
}




/*********************************************************************
NAME       : GetIncoming
DESCRIPTION: Returns the vector decribing the incoming direction.
PARAMETER  : NONE
RETURN     : CVector
EXCEPTION  : NONE.
*********************************************************************/

CVector CIntersectionInfo ::GetIncoming()
{
	return m_vecIncoming;
}


/*********************************************************************
NAME       : GetIntersectionType
DESCRIPTION: REturn the type of intersection
PARAMETER  : NONE
RETURN     : EIntersectionType
EXCEPTION  : NONE.
*********************************************************************/

EIntersectionType CIntersectionInfo ::GetIntersectionType()
{
	return m_eIntersectionType;
}


/*********************************************************************
NAME       : SetPointOfIntersection
DESCRIPTION: Set the point of intersection
PARAMETER  : pt	: The new point of intersection.
RETURN     : void
EXCEPTION  : NONE.
*********************************************************************/

void CIntersectionInfo::SetPointOfIntersection(CPoint3D pt)
{
	m_ptIntersection = pt;
}


/*********************************************************************
NAME       : SetNormal
DESCRIPTION: Set the Normal vector
PARAMETER  : vecNormal : the new Normal vector
RETURN     : void
EXCEPTION  : NONE.
*********************************************************************/

void CIntersectionInfo::SetNormal				(CVector vecNormal)
{
	m_vecNormal = vecNormal;
}


/*********************************************************************
NAME       : SetColor
DESCRIPTION: Set the point color of the hit object.
PARAMETER  : colObject	: The new color
RETURN     : void
EXCEPTION  : NONE.
*********************************************************************/

void CIntersectionInfo::SetColor				(CColor colObject)
{
	m_colObject = colObject;
}



/*********************************************************************
NAME       : SetTexCoords
DESCRIPTION: Set the texture coordinates
PARAMETER  : texCoords	: The new texture coordinates.
RETURN     : void
EXCEPTION  : NONE.
*********************************************************************/

void CIntersectionInfo::SetTexCoords			(CTexCoords texCoords)
{
	m_texIntersection = texCoords;
}

CIntersectionInfo::~CIntersectionInfo()
{

}
