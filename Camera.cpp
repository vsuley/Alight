// Camera.cpp: implementation of the CCamera class.
//
//////////////////////////////////////////////////////////////////////

# include "Camera.h"
# include "Shape.h"
# include "Log.h"
# include "IntersectionInfo.h"
# include "Scene.h"

# include <Math.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

// global variables
extern CLog	g_Log;

CCamera::CCamera()
{
}


CCamera::~CCamera()
{

}



/*********************************************************************
NAME       : CCamera
DESCRIPTION: Parameterized constructor.
PARAMETER  : ptPosition	: The position of the camera in 3D space.
			 vecUp		: The up vector
			 vecLookAt	: The Lookat Vector
RETURN     : NONE
EXCEPTION  : NONE.
*********************************************************************/

CCamera::CCamera(CPoint3D ptPosition, CVector vecUp, CVector vecLookAt, 
					float fViewAngle, float fFilmPlane, float fAspect)
{
	// Set the values that we have been passed.
	m_ptPosition= ptPosition;

	m_vecLookAt	= vecLookAt;
	m_vecLookAt.Normalize();
	
	m_vecUp		= m_vecLookAt.GetOrthoAlong(vecUp);
	m_vecUp.Normalize();
	

	m_fAngleOfView		= fViewAngle;
	m_fAspectRatio		= fAspect;
	m_fFilmPlaneDistance	= fFilmPlane;
}



/*********************************************************************
NAME       : GetRay
DESCRIPTION: This function calculates the ray representing a point on the
			 film plane represented in fractional width and height of hte
			 film rectangle.

PARAMETER  : dFractionX	: The coordinate along the width of the film rectangle
						  specified as a fraction.
			 dFractionY : The coordinate along the height of the film rect
						  specified as a fraction
RETURN     : A ray from center of camera to point on film plane.
EXCEPTION  : NONE.
*********************************************************************/

CRay CCamera::GetRay(double dFractionX, double dFractionY)
{
	CVector tempVec;
    CPoint3D ptOnFilmPlane;
    
    tempVec = (m_vecWidth * (float)dFractionX) + (m_vecHeight * (float)dFractionY);

	ptOnFilmPlane = m_ptTopLeftOfFilm + tempVec;

	return CRay (m_ptPosition, ptOnFilmPlane, IOR_AIR);
}



/*********************************************************************
NAME       : Describe
DESCRIPTION: This method dumps a description of the camera on the screen for 
             debugging.
PARAMETER  : NONE
RETURN     : void
EXCEPTION  : NONE.
*********************************************************************/

void CCamera::Describe()
{
    printf("\nPosition: (%f, %f, %f, %f)", m_ptPosition.GetX(), m_ptPosition.GetY(), m_ptPosition.GetZ(), m_ptPosition.GetW());
    printf("\nLookAt: (%f, %f, %f)", m_vecLookAt.XComponent(), m_vecLookAt.YComponent(),m_vecLookAt.ZComponent());
    printf("\nUp: (%f, %f, %f)", m_vecUp.XComponent(), m_vecUp.YComponent(),m_vecUp.ZComponent());
    
    printf("\nFilmPlaneDistance: %f", m_fFilmPlaneDistance);
    printf("\nAngle of view: %f", m_fAngleOfView);
    printf("\nAspect: %f", m_fAspectRatio);
    
    printf("\nWidth: (%f, %f, %f)", m_vecWidth.XComponent(), m_vecWidth.YComponent(), m_vecWidth.ZComponent());
    printf("\nHeight: (%f, %f, %f)", m_vecHeight.XComponent(), m_vecHeight.YComponent(), m_vecHeight.ZComponent());
    
    printf("\nTop Left: (%f, %f, %f, %f)", m_ptTopLeftOfFilm.GetX(), m_ptTopLeftOfFilm.GetY(), m_ptTopLeftOfFilm.GetZ(), m_ptTopLeftOfFilm.GetW());
}


/*********************************************************************
NAME       : Initialize
DESCRIPTION: This function uses the parameters of the camera set by the
			 user to calculate some of the other variables which make
			 the camera ready to use.

			 Extended information
			   Initialize the camera. what is this?
			   Well, we have taken a huge list of parameters from the user to
			   set the camera. These include the position of the camera, the 
			   field of vision along the y axis, the aspect ratio, the look at
			   vector, the up vector, the pixel resolution, the distance of teh 
			   film plane. 
			   If you look at it more closesly, the purpose of all these
			   is just to help us spawn the 'pixel' rays in the right direction.
			   We then check these rays for intersection etc and we compute their
			   color and we paint it onscreen. 
			   As i just said, we have to be able to compute the rays. We consider
			   an imaginary rectangle in front of the camera which behaves as the 
			   projection plane or as I have used, the film plane. The top left corner
			   of this rectangle gets mapped to the top left corner of the 
			   rendering window (please note that in free 3D orientation, top-left
			   is not exactly 'top' and 'left'!).
			   Thus the parameters we need to create the rays are the initial
			   top-left corner. After we keep adding the col-increment and row-
			   increment values to get the next successive point on the film plane.

			   Thus, the initialize function computes the top-left, col increment
			   and row increment for us.

PARAMETER  : NONE
RETURN     : void
EXCEPTION  : NONE.
*********************************************************************/

void CCamera::Initialize()
{
	double	 dHeight;
	double	 dWidth;
	double	 dViewAngleRadians;
	CPoint3D m_ptFilmCenter;
	
	const double PI = 3.1415926535;

	/*****************************************************************
	STRATEGY:
	1. Calculate the height of the film plane in world coordinates.
	2. Calculate the width of the film plane in world coordinates.
	3. Calculate the center of the film plane.
	4. Calculate the top-left corner of the film plane.
	5. Calculate the column increment.
	6. Calculate the row increment.
	*****************************************************************/

	// 1.
	dViewAngleRadians = (double)m_fAngleOfView * (double)PI / (double)180.0f;
	
	dHeight = 2 * (m_fFilmPlaneDistance) * tan ( dViewAngleRadians / 2.0f);

	// 2.
	dWidth	= dHeight / (double)m_fAspectRatio;

	// 3.
	m_ptFilmCenter = (m_ptPosition + (m_vecLookAt * m_fFilmPlaneDistance));

	// 4.
	CVector vecToTop, vecToLeft;
	
	vecToTop			= m_vecUp * ((float)(0.5 * dHeight));
	vecToLeft			= (m_vecLookAt.CrossProduct(m_vecUp)).Normalize() * ((float) (0.5 * dWidth));

	m_ptTopLeftOfFilm	= (m_ptFilmCenter + (vecToTop + vecToLeft));

	// 5.
	// This line deserves some attention.
	m_vecWidth	= (m_vecUp.CrossProduct(m_vecLookAt)).Normalize() * (float)dWidth; 

	// 6.
	// The -1 is multiplied becuase the rows move down, so it is actually a 'decrement'. 
	// However, algebraicaly it all just takes care of itself.
	m_vecHeight = m_vecUp * (-1.0f) * (float)dHeight;
}