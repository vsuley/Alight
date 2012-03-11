// CheckerBoard.cpp: implementation of the CCheckerBoard class.
//
//////////////////////////////////////////////////////////////////////

#include "CheckerBoard.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCheckerBoard::CCheckerBoard()
{

}

CCheckerBoard::~CCheckerBoard()
{

}



/*********************************************************************
NAME       : CCheckerBoard
DESCRIPTION: Parameterized Constructor
PARAMETER  : (Lots)
RETURN     : NONE
EXCEPTION  : NONE.
*********************************************************************/

CCheckerBoard::CCheckerBoard(CColor col1Diff, CColor col1Amb, CColor col1Spec, CColor col2Diff, CColor col2Amb, CColor col2Spec, float fTile)
{
	m_Color1Diffuse = col1Diff;
	m_Color1Ambient = col1Amb;
	m_Color1Specular= col1Spec;
	
	m_Color2Diffuse = col2Diff;
	m_Color2Ambient = col2Amb;
	m_Color2Specular= col2Spec;

	m_fTile = fTile;
}

/*********************************************************************
NAME       : GetDiffuseColorAt
DESCRIPTION: Returns the diffuse color at teh specified texture coord.
PARAMETER  : texCoords	: The texture Coordinates.
RETURN     : CColor
EXCEPTION  : NONE.
*********************************************************************/

CColor CCheckerBoard::GetDiffuseColorAt	(CIntersectionInfo hitInfo)
{
	float u;
	float v;

	/*******************************************************************
	NOTE:
	This is the most important function of the class as it decides which
	color to return. We take the u, v coordinates from teh parameter 
	and compute the appropriate color to display at that point.
	*******************************************************************/

	/*******************************************************************
	STRATEGY:
	1. Get the u and v components from the parameter.
	2. Scale them to incorporate tiling.
	3. Get teh decimal part of the floating point number.
	4. Compute the color depending on the u and v.
	*******************************************************************/

	// 1.
	u = hitInfo.GetTextureCoordinates().getU();
	v = hitInfo.GetTextureCoordinates().getV();

	// 2.
	u = u * m_fTile;
	v = v * m_fTile;
	
	// 3.
	u = u - (int)u;
	v = v - (int)v;

	// 4.
	if(u < 0.5f)
	{
		if(v < 0.5f)
		{
			return m_Color1Diffuse;
		}
		else
		{
			return m_Color2Diffuse;
		}
	}
	else
	{
		if (v < 0.5f)
		{
			return m_Color2Diffuse;
		}
		else
		{
			return m_Color1Diffuse;
		}
	}
}



/*********************************************************************
NAME       : GetAmbientColorAt
DESCRIPTION: Returns the ambient color at teh specified texture coord.
PARAMETER  : texCoords	: The texture Coordinates.
RETURN     : CColor
EXCEPTION  : NONE.
*********************************************************************/

CColor CCheckerBoard::GetAmbientColorAt	(CIntersectionInfo hitInfo)
{
	float u, v;

	/*******************************************************************
	STRATEGY:
	1. Get the u and v components from the parameter.
	2. Scale them to incorporate tiling.
	3. Get teh decimal part of the floating point number.
	4. Compute the color depending on the u and v.
	*******************************************************************/

	// 1.
	u = hitInfo.GetTextureCoordinates().getU();
	v = hitInfo.GetTextureCoordinates().getV();

	// 2.
	u = u * m_fTile;
	v = v * m_fTile;
	
	// 3.
	u = u - (int)u;
	v = v - (int)v;

	// 4.
	if(u < 0.5f)
	{
		if(v < 0.5f)
		{
			return m_Color1Ambient;
		}
		else
		{
			return m_Color2Ambient;
		}
	}
	else
	{
		if (v < 0.5f)
		{
			return m_Color2Ambient;
		}
		else
		{
			return m_Color1Ambient;
		}
	}
}





/*********************************************************************
NAME       : GetSpecularColorAt
DESCRIPTION: Returns the specular color at teh specified texture coord.
PARAMETER  : texCoords	: The texture Coordinates.
RETURN     : CColor
EXCEPTION  : NONE.
*********************************************************************/

CColor CCheckerBoard::GetSpecularColorAt	(CIntersectionInfo hitInfo)
{
	float u,v;
	
	/*******************************************************************
	STRATEGY:
	1. Get the u and v components from the parameter.
	2. Scale them to incorporate tiling.
	3. Get teh decimal part of the floating point number.
	4. Compute the color depending on the u and v.
	*******************************************************************/

	// 1.
	u = hitInfo.GetTextureCoordinates().getU();
	v = hitInfo.GetTextureCoordinates().getV();

	// 2.
	u = u * m_fTile;
	v = v * m_fTile;
	
	// 3.
	u = u - (int)u;
	v = v - (int)v;

	// 4.
	if(u < 0.5f)
	{
		if(v < 0.5f)
		{
			return m_Color1Specular;
		}
		else
		{
			return m_Color2Specular;
		}
	}
	else
	{
		if (v < 0.5f)
		{
			return m_Color2Specular;
		}
		else
		{
			return m_Color1Specular;
		}
	}
}
