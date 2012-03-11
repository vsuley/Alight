// TextureMap.h: interface for the CTextureMap class.
//
//////////////////////////////////////////////////////////////////////

# ifndef _TEXTUREMAP_H
# define _TEXTUREMAP_H

# include "IntersectionInfo.h"
# include "Color.h"

class CIntersectionInfo;

class CTextureMap  
{
public:
	CTextureMap();
	virtual ~CTextureMap();

	virtual CColor GetDiffuseColorAt	(CIntersectionInfo hitInfo)=0;
	virtual CColor GetAmbientColorAt	(CIntersectionInfo hitInfo)=0;
	virtual CColor GetSpecularColorAt	(CIntersectionInfo hitInfo)=0;

};

# endif