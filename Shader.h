// Shader.h: interface for the CShader class.
//
//////////////////////////////////////////////////////////////////////

# ifndef _SHADER_H
# define _SHADER_H


# include "IntersectionInfo.h"
# include "TextureMap.h"

class CIntersectionInfo;
class CTextureMap;

class CShader  
{
public:
	CShader();
	CShader(bool isTextured);
	
	void AssignTexture (CTextureMap* texMap) 
	{
		m_pTexMap = texMap;
	}
	
	virtual ~CShader();
	
	// Object Interface.
	virtual CColor	ShadePoint(CIntersectionInfo hitInfo) = 0;

protected:
	
	CTextureMap *m_pTexMap;

	bool m_bTextureMap;
};

# endif