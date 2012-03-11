// FancyTile1.h: interface for the CFancyTile class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FANCYTILE1_H__CA4BC257_6E4D_40FC_A2B9_0014D36900CF__INCLUDED_)
#define AFX_FANCYTILE1_H__CA4BC257_6E4D_40FC_A2B9_0014D36900CF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "TextureMap.h"

class CFancyTile : public CTextureMap  
{
public:
	CFancyTile();
	virtual ~CFancyTile();

	CFancyTile(CColor borderDiff, CColor borderAmbient, CColor borderSpecular, 
					CColor baseDiff, CColor baseAmbient, CColor baseSpecular, 
						CColor TikliDiff, CColor TikliAmbient, CColor TikliSpecular, 
							float tile, float borderWidth, float tikliWidth);

	virtual CColor GetDiffuseColorAt	(CIntersectionInfo hitInfo);
	virtual CColor GetAmbientColorAt	(CIntersectionInfo hitInfo);
	virtual CColor GetSpecularColorAt	(CIntersectionInfo hitInfo);

protected:

	CColor m_BorderDiffuse;
	CColor m_BorderAmbient;
	CColor m_BorderSpecular;
	
	CColor m_BaseDiffuse;
	CColor m_BaseAmbient;
	CColor m_BaseSpecular;
	
	CColor m_TikliDiffuse;
	CColor m_TikliAmbient;
	CColor m_TikliSpecular;

	float m_fTile;
	float m_fBorderWidth;
	float m_fTikliWidth;
};

#endif // !defined(AFX_FANCYTILE1_H__CA4BC257_6E4D_40FC_A2B9_0014D36900CF__INCLUDED_)
