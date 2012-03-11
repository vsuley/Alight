// Phong.cpp: implementation of the CPhong class.
//
//////////////////////////////////////////////////////////////////////

# include "Phong.h"
# include "Light.h"
# include "Scene.h"
# include <math.h>
# include <iostream>

using namespace std;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
extern CScene g_objScene;

CPhong::CPhong()
{

}

CPhong::~CPhong()
{

}

CPhong::CPhong(CColor colDiffuse, CColor colAmbient, CColor colSpecular, float strength, float coeff, float diffuse, float reflection, float transmission, bool isTextured) : CShader(isTextured)
{
	this->m_colAmbient			= colAmbient;
	this->m_colDiffuse			= colDiffuse;
	this->m_colSpecular			= colSpecular;
	this->m_fSpecularCoeff		= coeff;
	this->m_fSpecularStrength	= strength;
	this->m_fDiffuseCoeff		= diffuse;
	this->m_fReflectionCoeff	= reflection;
	this->m_fTransmissionCoeff	= transmission;
}




/*********************************************************************
NAME       : ShadePoint
DESCRIPTION: This function computes the color of the point specified inside
		     hitInfo using Phong's method.
PARAMETER  : hitInfo	: the information about the object intersection.
RETURN     : The final color of the sampled point as CCOlor
EXCEPTION  : NONE
*********************************************************************/

CColor CPhong::ShadePoint(CIntersectionInfo hitInfo)
{
	int			iNumLights;

	CLight**	ppLights;
	
	iNumLights	= g_objScene.GetNumLights();
	ppLights	= g_objScene.GetLights();

	CColor		colFinal(0,0,0);

	if(m_fDiffuseCoeff > 0) {
		colFinal += DiffuseReflection(hitInfo, ppLights, iNumLights);
	}
	
	if (m_fReflectionCoeff > 0) {
		colFinal += SpecularReflection(hitInfo) * m_fReflectionCoeff;
	}

	if (m_fTransmissionCoeff > 0) {
		colFinal += Transmitted(hitInfo) * m_fTransmissionCoeff;
	}
	
	return colFinal;
}






/*********************************************************************
NAME       : DiffuseReflection
DESCRIPTION: This function computes the diffuse reflection off a surfae
			 using Phongs equation. Note that specular hightlights are 
			 also a part of the color returned. Specular reflection is 
			 mirror - reflection. 
PARAMETER  : hitInfo	: the information about the object intersection.
			 ppLights	: An array of pointers to all lights
			 iNumLights	: The total number of lights in the scene
RETURN     : The diffuse color
EXCEPTION  : NONE
*********************************************************************/

CColor CPhong::DiffuseReflection(CIntersectionInfo hitInfo, CLight** ppLights, int iNumLights)
{
	CColor colDiff(0,0,0);

	/*************************************************************************
	STRATEGY:
	1. Loop through all the lights to calculate the color value.
	2. Add in Ambient color.
	3. Return the calculated color
	*************************************************************************/

	// 1.
	for (int i = 0; i < iNumLights; i++)
	{
		/********************************************************************
		LOOP LOGIC:
		1.1. Get the ray from the point of intersection to the light source.
		1.2. Check if it is unobstructed. If yes, then use the light. 
		********************************************************************/

		
		// 1.1.
		CRay	rayObjectToLight(hitInfo.GetPointOfIntersection(), ppLights[i]->GetPosition(), IOR_AIR);

		// 1.2.
		if( g_objScene.IsUnobstructed(rayObjectToLight) )
		{
			/*************************************************************************
			LOGIC:
			1.2.1. Calculate the diffuse term.
			       diffuse = (material Color * Light Color) * Dot Product(normal.ray)
			1.2.2. Calculate the specular highlight.
			*************************************************************************/

			// 1.2.1.
				CColor	colToUse;

				/********************************************************************
				If we are using a texture map, the color at the point will not simply 
				be the color of the object, in this case, calculate the color at teh point.

				1.2.1.1. Check if we are texture mapped. If yes then get color from
						 texture, or assign the object color.
				1.2.1.2. Use the stated equation to calculate the color.
				********************************************************************/
				
				// 1.2.1.1.
				if (m_bTextureMap)	colToUse = m_pTexMap->GetDiffuseColorAt(hitInfo);
				else				colToUse = m_colDiffuse;

				// 1.2.1.2.
				float dotProduct = (float)hitInfo.GetNormal().DotProduct(rayObjectToLight.Direction());
				colDiff += (colToUse * ppLights[i]->GetColor()) *  dotProduct * m_fDiffuseCoeff;
				
			// 1.2.2.
				/**************************************************************************
				Sub Logic:
				
				To calculate the specular highlight, we use the following formula:

				specHighlight = (mat * light col) * Power(DotProd(reflective dire . view direction), specExponent)

				Thus, we first have to calculate the reflective direction and view vector.

				1.2.2.1. Calculate Reflective direction.
				1.2.2.2. Get view direction
				1.2.2.3. Calculate spec highlight
				**************************************************************************/
				
				CVector vecReflective;

				// 1.2.2.1.
				vecReflective = rayObjectToLight.Direction() - hitInfo.GetNormal() * (2.0f * rayObjectToLight.Direction().DotProduct(hitInfo.GetNormal()));
				vecReflective.Normalize();

				// 1.2.2.2.
				CVector vecView;

				vecView = hitInfo.GetIncoming();

				// 1.2.2.3.
				if (m_bTextureMap)	colToUse = m_pTexMap->GetSpecularColorAt(hitInfo);
				else				colToUse = m_colSpecular;

				try {
					
					float dotProd = (float)((int)vecReflective.DotProduct(vecView) * 1000.0f) / 1000.0f;
					
					colDiff += (colToUse  * ppLights[i]->GetColor()) * (float)pow( dotProd , m_fSpecularCoeff) * m_fSpecularStrength;
				}
				catch (...) {
					
					cout << "Exception";
				}
		
		} // ~if
	}

	// 2.
	if (m_bTextureMap)
	{
		colDiff += m_pTexMap->GetAmbientColorAt(hitInfo);
	}
	else 
	{
		colDiff += m_colAmbient;
	}

	// 3.
	return colDiff;
}






/*********************************************************************
NAME       : SpecularReflection
DESCRIPTION: This method models perfect specular reflection.
PARAMETER  : hitInfo	: the information about the object intersection.
RETURN     : The color at the point of intersection caused due to specular
		     (mirror) reflection.
EXCEPTION  : NONE
*********************************************************************/

CColor CPhong::SpecularReflection(CIntersectionInfo hitInfo)
{
	CVector vecIncoming;
	CRay	rayReflected;
	CVector	vecNormal;
	CColor	colReflected;
	CIntersectionInfo hitReflection;

	/*****************************************************************
	STRATEGY:
	1. Determine the reflected ray.
	2. Test the scene graph for collisions with the reflected ray.
	3. Get the color at the point of intersection.
	4. Modify the color as needed.
	5. Return the color.
	*****************************************************************/

	// 1.
		/**************************************************************
		Reflected ray:
		Use the following formula:

		r = S - n * (2 (S . n)/ (sqaure of |n|))

		Where S is the incoming vector, n is the normal. |n| is unity 
		thus square of n can be ignored.

		1.1. Get incoming vector.
		1.2. Get normal
		1.3. Use formula to calculate reflected ray.
		1.4. Now translate this ray to the point of intersection.
		**************************************************************/
		
		// 1.1.
		vecIncoming = hitInfo.GetIncoming();

		// 1.2.
		vecNormal	= hitInfo.GetNormal();

		// 1.3.
		rayReflected = CVector(vecIncoming - (vecNormal * (2.0f * vecIncoming.DotProduct(vecNormal))));

		// 1.4.
		rayReflected.Translate(hitInfo.GetPointOfIntersection());

	// 2.
	hitReflection = g_objScene.TestRayForClosest (rayReflected);

	// 3.
	CShape* shape = 0;
	shape = hitReflection.GetShape();

	colReflected = shape->ShadePoint(hitReflection);

	// 4.
	// No modification as of now.

	// 5.
	return colReflected;
}






/*********************************************************************
NAME       : ShadePoint
DESCRIPTION: This function computes the color of the point specified inside
		     hitInfo using Phong's method.
PARAMETER  : hitInfo	: the information about the object intersection.
RETURN     : The final color of the sampled point as CCOlor
EXCEPTION  : NONE
*********************************************************************/

CColor CPhong::Transmitted(CIntersectionInfo hitInfo)
{
	float	IORCurrent;
	float	IORNext;
	float	IORRelative;

	float	cosAngleInc;
	float	cosAngleRef;

	CVector vecIncident;
	CVector vecResultant;
	CVector	vecNormal;
	CRay	rayTransmission;
	
	EIntersectionType eType;

	CIntersectionInfo hitTransmission;
	CColor colTransmitted;

	/****************************************************************
	STRATEGY:
	1. Get the neccessary data.
	2. Compute the direction of the transmitted ray.
	3. Test for intersections.
	4. Ask the object intersected for the color
	5. Tweak the color as required.
	6. Return the color.

	****************************************************************/

	// 1.
		/***********************************************************
		1.1. Find out if we are entering or exiting.
		1.2. If we are entering then the current medium is air and the
			 next medium is glass. If we are exiting then the current
			 medium is glass and the next medium is air.
		1.3. Get the incident vector.
		***********************************************************/
		
		// 1.1.
		eType = hitInfo.GetIntersectionType();

		// 1.2.
		if (eType == ENTRY) {
			IORCurrent	= IOR_AIR;
			IORNext		= IOR_GLASS;
		}
		else {
			IORCurrent = IOR_GLASS;
			IORNext = IOR_AIR;
		}

		// 1.3.
		vecIncident = hitInfo.GetIncoming();

	// 2.
		/*************************************************************
		2.1. Compute the relative index of refraction.
		2.2. Compute the normal in the facing direction.
		2.3. Compute cos of angle of incidence.
		2.4. Compute cos of angle of refraction.
		2.5. Compute the transmitted vector.
		*************************************************************/

		// 2.1.
		IORRelative = IORNext / IORCurrent;

		// 2.2.
		if (eType == ENTRY) {
			vecNormal = hitInfo.GetNormal() * -1.0f;
		}else {
			vecNormal = hitInfo.GetNormal();
		}
		
		// 2.3.
		cosAngleInc = vecIncident.DotProduct( hitInfo.GetNormal() * -1.0f);

		// 2.4.
		cosAngleRef	 = IORRelative * (float)sqrt(1.0f - (1.0f/ (IORRelative * IORRelative)) * (1.0f - cosAngleInc * cosAngleInc));
		
		// 2.5.
		vecResultant = (vecIncident * (1.0f / IORRelative)) - (vecNormal * (cosAngleRef - cosAngleInc / IORRelative));

	// 3.
	rayTransmission = vecResultant;
	rayTransmission.Translate(hitInfo.GetPointOfIntersection() );
	
	hitTransmission = g_objScene.TestRayForClosest (rayTransmission);
	
	// 4.
	CShape* shape = 0;
	shape = hitTransmission.GetShape();
	
	try {
		colTransmitted = shape->ShadePoint(hitTransmission);

	}
	catch (...) {

	}

	// 5.
	// No modification as of now.

	// 6.
	return colTransmitted;
}
