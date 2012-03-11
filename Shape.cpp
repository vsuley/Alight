// Shape.cpp: implementation of the CShape class.
//
//////////////////////////////////////////////////////////////////////

# include "Shape.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CShape::CShape()
{
	m_pShader	= 0;
}

CShape::~CShape()
{

}
	

/*********************************************************************
NAME       : CShape
DESCRIPTION: parameterized constructor
PARAMETER  : pos	: the position of the shape in space
			 col	: the color of the shape.
RETURN     : NONE
EXCEPTION  : NONE
*********************************************************************/

CShape::CShape(CPoint3D pos, CColor col):COnScreenObject (pos)
{
	this->objColor = col;
	m_pShader = 0;
}



/*********************************************************************
NAME       : SetObjectColor
DESCRIPTION: Sets the color of the shape
PARAMETER  : col	: the color of the shape
RETURN     : NONE
EXCEPTION  : NONE
*********************************************************************/

void	CShape::SetObjectColor		(CColor col)
{
	this->objColor = col;
}





/*********************************************************************
NAME       : GetObjectColor
DESCRIPTION: Gets the color of the shape
PARAMETER  : NONE
RETURN     : The CColor object describing the color of the object
EXCEPTION  : NONE
*********************************************************************/

CColor CShape::GetObjectColor()
{
	return objColor;
}





/*********************************************************************
NAME       : AssignShader
DESCRIPTION: Assigns a shader to the shape object.
PARAMETER  : NONE
RETURN     : The CColor object describing the color of the object
EXCEPTION  : NONE
*********************************************************************/

void CShape::AssignShader(CShader* shader)
{
	m_pShader = shader;
}