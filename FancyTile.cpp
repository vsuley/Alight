// FancyTile1.cpp: implementation of the CFancyTile class.

//

//////////////////////////////////////////////////////////////////////



#include "FancyTile.h"



//////////////////////////////////////////////////////////////////////

// Construction/Destruction

//////////////////////////////////////////////////////////////////////



CFancyTile::CFancyTile()

{



}



CFancyTile::~CFancyTile()

{



}



CFancyTile::CFancyTile(CColor borderDiff, CColor borderAmbient, CColor borderSpecular, 

					CColor baseDiff, CColor baseAmbient, CColor baseSpecular, 

						CColor TikliDiff, CColor TikliAmbient, CColor TikliSpecular, 

							float tile, float borderWidth, float tikliWidth)

{

	m_BorderDiffuse = borderDiff;

	m_BorderAmbient = borderAmbient;

	m_BorderSpecular = borderSpecular;

	

	m_BaseDiffuse = baseDiff;

	m_BaseAmbient = baseAmbient;

	m_BaseSpecular = baseSpecular;

	

	m_TikliDiffuse = TikliDiff;

	m_TikliAmbient = TikliAmbient;

	m_TikliSpecular = TikliSpecular;



	m_fTile = tile;

	m_fBorderWidth = borderWidth;

	m_fTikliWidth = tikliWidth;



}



/*********************************************************************

NAME       : GetDiffuseColorAt

DESCRIPTION: Returns the diffuse color at teh specified texture coord.

PARAMETER  : texCoords	: The texture Coordinates.

RETURN     : CColor

EXCEPTION  : NONE.

*********************************************************************/



CColor CFancyTile::GetDiffuseColorAt	(CIntersectionInfo hitInfo)

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

	if (u < m_fBorderWidth || u > 1.0f - m_fBorderWidth || v < m_fBorderWidth || v > 1.0f - m_fBorderWidth)

		return m_BorderDiffuse;



	if ( (u < m_fTikliWidth && v < m_fTikliWidth) || 

			(u < m_fTikliWidth && v > 1.0f - m_fTikliWidth) || 

				(u > 1.0f - m_fTikliWidth && v < m_fTikliWidth) || 

					(u > 1.0f - m_fTikliWidth && v > 1.0f - m_fTikliWidth))

		return m_TikliDiffuse;



		

	return m_BaseDiffuse;

}







/*********************************************************************

NAME       : GetAmbientColorAt

DESCRIPTION: Returns the ambient color at teh specified texture coord.

PARAMETER  : texCoords	: The texture Coordinates.

RETURN     : CColor

EXCEPTION  : NONE.

*********************************************************************/



CColor CFancyTile::GetAmbientColorAt	(CIntersectionInfo hitInfo)

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

	if (u < m_fBorderWidth || u > 1.0f - m_fBorderWidth || v < m_fBorderWidth || v > 1.0f - m_fBorderWidth)

		return m_BorderAmbient;



	if ( (u < m_fTikliWidth && v < m_fTikliWidth) || 

			(u < m_fTikliWidth && v > 1.0f - m_fTikliWidth) || 

				(u > 1.0f - m_fTikliWidth && v < m_fTikliWidth) || 

					(u > 1.0f - m_fTikliWidth && v > 1.0f - m_fTikliWidth))

		return m_TikliAmbient;



	

	return m_BaseAmbient;

}











/*********************************************************************

NAME       : GetSpecularColorAt

DESCRIPTION: Returns the specular color at teh specified texture coord.

PARAMETER  : texCoords	: The texture Coordinates.

RETURN     : CColor

EXCEPTION  : NONE.

*********************************************************************/



CColor CFancyTile::GetSpecularColorAt	(CIntersectionInfo hitInfo)

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

	if (u < m_fBorderWidth || u > 1.0f - m_fBorderWidth || v < m_fBorderWidth || v > 1.0f - m_fBorderWidth)

		return m_BorderSpecular;



	if ( (u < m_fTikliWidth && v < m_fTikliWidth) || 

			(u < m_fTikliWidth && v > 1.0f - m_fTikliWidth) || 

				(u > 1.0f - m_fTikliWidth && v < m_fTikliWidth) || 

					(u > 1.0f - m_fTikliWidth && v > 1.0f - m_fTikliWidth))

		return m_TikliSpecular;



	

	return m_BaseSpecular;

}

