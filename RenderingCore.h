// RenderingCore.h: interface for the CRenderingCore class.
//
//////////////////////////////////////////////////////////////////////

# ifndef _RENDERINGCORE_H
# define _RENDERINGCORE_H

# include "Camera.h"
# include "Color.h"
# include <math.h>

# define L_MAX 1000.0f
# define LD_MAX 100.0f

# define XRES 640
# define YRES 480

# define RED_CHANNEL 0
# define GREEN_CHANNEL 1
# define BLUE_CHANNEL 2

class CRenderingCore  
{
public:
				CRenderingCore();
	virtual		~CRenderingCore();
	void		Render();
protected:
	
	CCamera*	m_pcamCurrent;
	int			m_iPixelX;
	int			m_iPixelY;
	int			m_iSupersampleDepth;
	float		m_ppPixelBuffer[3][XRES][YRES];
	
	// protected functions:
	CColor Sample(float x, float y, int curDepth);
	void RenderPixelBuffer();
	void DrawOnScreen();
	void WardToneReproduction();
	void ReinhardToneReproduction();
};


# endif
