// Scene.h: interface for the CScene class.
//
//////////////////////////////////////////////////////////////////////

# ifndef _SCENE_H
# define _SCENE_H

# include "Triangle.h"
# include "Plane.h"
# include "Sphere.h"
# include "Shape.h"
# include "IntersectionInfo.h"
# include "Light.h"
# include "Environment.h"
# include "GlobalConstants.h"

class CShape;
class CCamera;

class CScene  
{
public:
	
	// Object Constructor
	CScene();

	// Object deConstructor
	virtual ~CScene();

	// Object Interface
	CIntersectionInfo	TestRayForClosest	(CRay ray);
	int					GetNumLights		();
	CLight**			GetLights			();
	CCamera*			GetCamera			();
	bool				IsUnobstructed		(CRay rayToTest);

protected:
	
	// Protected Object variables
	int		m_iShapeCount;
	int		m_iLightCount;
	int		m_iCamCount;

	CShape	*m_objShapes[40];

	CLight	*m_objLights[256];

	CCamera *m_objCameras[1];

	CEnvironment m_objEnvironment;

	// protected methods
	bool	isEntry(CVector vecIncoming, CVector vecNormal);

	void	CreateFloor();
	void	CreateReflectiveBall();
	void	CreateCrystalBall();
	void	CreateTriangle();
	void	CreateMesh();
	void	CreateLights();
	void	CreateCamera();
};

# endif