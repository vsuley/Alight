// Phong.h: interface for the CPhong class.
//
//////////////////////////////////////////////////////////////////////


# ifndef _PHONG_H
# define _PHONG_H

# include "Shader.h"
# include "Color.h"
# include "Light.h"

class CPhong : public CShader  
{
public:
	
	// Object construction
	CPhong();
	CPhong(CColor diffuse, CColor ambient, CColor specular, float strength, float coeff, float , float, float, bool);
	
	// Object destruction
	virtual ~CPhong();

	// Object interface
	CColor  ShadePoint(CIntersectionInfo hitInfo);

protected:
	CColor	m_colDiffuse;
	CColor	m_colAmbient;
	CColor	m_colSpecular;
	float	m_fSpecularStrength;
	float	m_fSpecularCoeff;

	float	m_fDiffuseCoeff;
	float	m_fReflectionCoeff;
	float	m_fTransmissionCoeff;

	// protected functions
	CColor DiffuseReflection	(CIntersectionInfo hitInfo, CLight** ppLights, int iNumLights);
	CColor SpecularReflection	(CIntersectionInfo hitInfo);
	CColor Transmitted			(CIntersectionInfo hitInfo);
	CColor GetColorAt			(CTexCoords texCoords);
};

# endif