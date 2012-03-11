// Camera.h: interface for the CCamera class.
//
//////////////////////////////////////////////////////////////////////

# ifndef _CAMERA_H
# define _CAMERA_H

# include "Vector.h"
# include "Ray.h"
# include "Point3D.h"

class CCamera  
{
public:
	
	// Object Constructors
	CCamera	();
	CCamera	(CPoint3D objPosition, CVector upVector, CVector objLookAt,float fViewAngle, float fFilmPlane, float fAspect); 
	
	// Object destruction
	virtual ~CCamera();

	// Object interface
	void	Initialize();
    void    Describe();
	CRay	GetRay (double dFilmFractionX, double dFilmFractionY);

protected:
	CVector		m_vecUp;
	CVector		m_vecLookAt;
	CPoint3D	m_ptPosition;
	
	float		m_fFilmPlaneDistance;
	float		m_fAngleOfView;
	float		m_fAspectRatio; // y by x

	CVector		m_vecWidth;
	CVector		m_vecHeight;

	CPoint3D	m_ptTopLeftOfFilm;
};


# endif