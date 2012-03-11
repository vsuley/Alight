// CheckerBoard.h: interface for the CCheckerBoard class.
//
//////////////////////////////////////////////////////////////////////


# ifndef _CHECKERBOARD_H
# define _CHECKERBOARD_H

#include "TextureMap.h"

class CCheckerBoard : public CTextureMap  
{
public:
	CCheckerBoard();
	CCheckerBoard(CColor col1Diff, CColor col1Amb, CColor col1Spec, CColor col2Diff, CColor col2Amb, CColor col2Spec, float fTile);
	virtual ~CCheckerBoard();

	virtual CColor GetDiffuseColorAt	(CIntersectionInfo hitInfo);
	virtual CColor GetAmbientColorAt	(CIntersectionInfo hitInfo);
	virtual CColor GetSpecularColorAt	(CIntersectionInfo hitInfo);

protected:

	CColor m_Color1Diffuse;
	CColor m_Color1Ambient;
	CColor m_Color1Specular;
	
	CColor m_Color2Diffuse;
	CColor m_Color2Ambient;
	CColor m_Color2Specular;

	float m_fTile;
};

# endif