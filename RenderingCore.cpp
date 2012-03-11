// RenderingCore.cpp: implementation of the CRenderingCore class.
//
//////////////////////////////////////////////////////////////////////

# include "RenderingCore.h"
# include "Scene.h"
# include "BMPFile.h"
# include <math.h>
# include <GLUT/glut.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


// External variables
extern CScene	g_objScene;

CRenderingCore::CRenderingCore()
{
	this->m_iPixelX		= XRES;
	this->m_iPixelY		= YRES;
	this->m_pcamCurrent = g_objScene.GetCamera();
	this->m_iSupersampleDepth = 2;
}

CRenderingCore::~CRenderingCore()
{

}


/*********************************************************************
NAME       : Render
DESCRIPTION: this is the main function that creates teh image on-screen.
PARAMETER  : NONE
RETURN     : void
EXCEPTION  : NONE.
*********************************************************************/
void CRenderingCore::Render() {

	// Raytrace process
	RenderPixelBuffer();
	
	// Post-processing
	WardToneReproduction();
	
	// Put it on screen.
	DrawOnScreen();
}


// The raytracing process
void CRenderingCore::RenderPixelBuffer()
{
    /**************************************************************
    STRATEGY:
    1. Run nested loop for the entire screen.
    **************************************************************/
    m_pcamCurrent->Describe();
    
    // 1.
    for (int y = 0; y < m_iPixelY; y++)
    {
		for (int x = 0; x < m_iPixelX; x++)
		{
			CColor colToUse;
			
            /****************************************************************
			NESTED LOOP LOGIC:
			Calculate the X fraction
			Get the pixel ray for this screen coordinate fromt the 
			camera
			Get the color for this ray.
			Plot the pixel with this color.
			****************************************************************/

			colToUse = Sample ((float)x, (float)y, 1);

			m_ppPixelBuffer[0][x][y] = ((float) (int)(colToUse.GetRed()   * 1000.0f)) / 1000.0f;
			m_ppPixelBuffer[1][x][y] = ((float) (int)(colToUse.GetGreen() * 1000.0f)) / 1000.0f;
			m_ppPixelBuffer[2][x][y] = ((float) (int)(colToUse.GetBlue()  * 1000.0f)) / 1000.0f;

		}
    }
}



// protected functions:
CColor CRenderingCore::Sample(float x, float y, int curDepth)
{
	CColor	colArray[5];
	CColor  finalCol;
	int		colCount = 1;
	double	 dXFraction;
	double	 dYFraction;

	/*******************************************************************
	STRATEGY:
	1. First compute the color for the central pixel.
	2. Check if we have to dive further into the oversampling recursion.
	3. Average the colors. 
	4. Return the color.
	*******************************************************************/

	// 1.
		/***********************************************************
		SUB_STEPS:
		1.1. Calculate the x and y fractions.
		1.2. Get the corresponding ray from the camera.
		1.3. Test the scene to see which object intersects the ray.
		1.4. Query the object for teh color of the point.
		***********************************************************/

		// 1.1.
		dYFraction = (double)y / (double)m_iPixelY;
		dXFraction = (double)x / (double)m_iPixelX;
        
		// 1.2.
		CRay ray = m_pcamCurrent->GetRay(dXFraction, dYFraction);
		// 1.3.
		CIntersectionInfo hitInfo = g_objScene.TestRayForClosest(ray);
		// 1.4.
		colArray[0] = hitInfo.GetShape()->ShadePoint(hitInfo);
	
	// 2.
	if (curDepth < m_iSupersampleDepth) 
	{
		colCount = 5;

		float inc = 1.0f / (float) pow(2.0f, (float)curDepth);

		colArray[1] = Sample (x + inc, y, curDepth + 1);
		colArray[2] = Sample (x - inc, y, curDepth + 1);
		colArray[3] = Sample (x, y + inc, curDepth + 1);
		colArray[4] = Sample (x, y - inc, curDepth + 1);
	}

	// 3.
	finalCol = CColor::Average(colArray, colCount);

	// 4.
	return finalCol;
}



void CRenderingCore::WardToneReproduction() {

	float fLwa, fDelta, fLw, fLogTerm;
	long  nNumPixels;
	float fScaleFactor;
	
	/*******************************************************
	STRATEGY:
	1. Initialize the variables
	2. Calculate the log term for Lwa
	3. Calculate Lwa.
	4. Calculate scale factor
	5. Scale all pixels again.
	*******************************************************/
	
	// 1.
	nNumPixels = XRES * YRES;
	fDelta = 0.1f;
	fLogTerm = 0.0f;
	
	// 2.
    for (int y = 0; y < m_iPixelY; y++)
    {
		for (int x = 0; x < m_iPixelX; x++)
		{
			float temp;
			/************************************************
			LOOP LOGIC:
			2.1. Scale the color values using L_MAX
			2.2. Find Lw
			2.3. Calculate teh log term
			2.4. Sum it cumulatively.
			************************************************/

			// 2.1.
			m_ppPixelBuffer[0][x][y] *= L_MAX;
			m_ppPixelBuffer[1][x][y] *= L_MAX;
			m_ppPixelBuffer[2][x][y] *= L_MAX;
			
			// 2.2.
			fLw = 0.27f * m_ppPixelBuffer[0][x][y] + 
						0.67f * m_ppPixelBuffer[1][x][y] + 
							0.06f * m_ppPixelBuffer[2][x][y];
			
			// 2.3.
			temp = log (fLw + fDelta);
			
			// 2.4.
			fLogTerm += temp;
		}
	}
	
	// 3.
	fLwa = exp ( (1.0f / (float)nNumPixels) * fLogTerm);
	
	// 4.
	float term1, term2;
	
	term1 = 1.219f + pow(LD_MAX/2.0f, 0.4f);
	term2 = 1.219f + pow(fLwa, 0.4);
	fScaleFactor = pow(term1 / term2, 2.5f) / LD_MAX;
	
	// 5.
    for (int y = 0; y < m_iPixelY; y++)
    {
		for (int x = 0; x < m_iPixelX; x++)
		{
 		 	m_ppPixelBuffer[0][x][y] *= fScaleFactor;
 		 	m_ppPixelBuffer[1][x][y] *= fScaleFactor;
 		 	m_ppPixelBuffer[2][x][y] *= fScaleFactor;
		}
	}		
}


void CRenderingCore::ReinhardToneReproduction() {
}


// The drawing.
void CRenderingCore::DrawOnScreen() {
		
    glBegin (GL_POINTS);
    
    for (int y = 0; y < m_iPixelY; y++)
    {
		for (int x = 0; x < m_iPixelX; x++)
		{
            glColor3f (m_ppPixelBuffer[0][x][y], 
                            m_ppPixelBuffer[1][x][y],
                                m_ppPixelBuffer[2][x][y]);
            glVertex2i (x, -y);
            //printf("%f|%f|%f", m_ppPixelBuffer[0][x][y], m_ppPixelBuffer[1][x][y],m_ppPixelBuffer[2][x][y]);
		}
	}
    
    glEnd();
}