// OnScreenObject.cpp: implementation of the COnScreenObject class.
//
//////////////////////////////////////////////////////////////////////

#include "OnScreenObject.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

COnScreenObject::COnScreenObject()
{

}

COnScreenObject::~COnScreenObject()
{

}


/*********************************************************************
NAME       : COnScreenObject
DESCRIPTION: parameterized constructor
PARAMETER  : pos	: The position in space of the object
RETURN     : NONE
EXCEPTION  : NONE.
*********************************************************************/

COnScreenObject::COnScreenObject (CPoint3D pos)
{
	this->m_ptPosition = pos;
}


/*********************************************************************
NAME       : COnScreenObject
DESCRIPTION: parameterized constructor
PARAMETER  : pos	: The position in space of the object
RETURN     : NONE
EXCEPTION  : NONE.
*********************************************************************/

COnScreenObject::COnScreenObject (const COnScreenObject & obj1)
{
	this->m_ptPosition = obj1.m_ptPosition;
}

	

/*********************************************************************
NAME       : SetPosition	
DESCRIPTION: Set the position of the object
PARAMETER  : pos	: The position in space of the object
RETURN     : void
EXCEPTION  : NONE.
*********************************************************************/
void COnScreenObject::SetPosition	(CPoint3D pos)
{
	this->m_ptPosition = pos;
}

	

/*********************************************************************
NAME       : GetPosition
DESCRIPTION: Retrieve the position of the object
PARAMETER  : NONE
RETURN     : CPoint3D
EXCEPTION  : NONE.
*********************************************************************/

CPoint3D COnScreenObject::GetPosition	()
{
	return m_ptPosition;
}