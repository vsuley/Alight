// TexCoords.cpp: implementation of the CTexCoords class.
//
//////////////////////////////////////////////////////////////////////

#include "TexCoords.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////



/*********************************************************************
NAME       : CTexCoords
DESCRIPTION: Default constructor
PARAMETER  : NONE
RETURN     : NONE
EXCEPTION  : NONE.
*********************************************************************/

CTexCoords::CTexCoords()
{
	m_fU = 0;
	m_fV = 0;
}




/*********************************************************************
NAME       : ~CTexCoords
DESCRIPTION: De constructor
PARAMETER  : NONE
RETURN     : NONE
EXCEPTION  : NONE.
*********************************************************************/

CTexCoords::~CTexCoords()
{

}





/*********************************************************************
NAME       : CTexCoords
DESCRIPTION: Parameterized constructor
PARAMETER  : fU	: The 'u' coordinate
			 fV : The 'v' coordinate.
RETURN     : NONE
EXCEPTION  : NONE.
*********************************************************************/

CTexCoords::CTexCoords(float fU, float fV)
{
	m_fU = fU;
	m_fV = fV;
}