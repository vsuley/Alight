// Scene.cpp: implementation of the CScene class.
//
//////////////////////////////////////////////////////////////////////

# include "Scene.h"
# include "Shader.h"
# include "Phong.h"
# include "Camera.h"
# include "Mesh.h"
# include "CheckerBoard.h"
# include "Texturemap.h"
# include "FancyTile.h"

# include <math.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

extern CColor g_objRed;		
extern CColor g_objGreen;	
extern CColor g_objBlue	;	
extern CColor g_objYellow;	


/*********************************************************************
NAME       : CScene
DESCRIPTION: Default constructor
PARAMETER  : NONE
RETURN     : NONE
EXCEPTION  : NONE.
*********************************************************************/

CScene::CScene() : m_objEnvironment(CPoint3D(0,0,0,0), CColor(0.2f, 0.2f, 0.4f))
{
	m_iShapeCount	= m_iLightCount	= m_iCamCount = 0;
	
	/**************************************************************************
								Creation of Shapes
	**************************************************************************/
	
	CreateFloor(); // Red Color
		
	CreateReflectiveBall(); // Green in color.
	
	CreateCrystalBall(); // all blue in color
	
	CreateLights();

	CreateCamera();
}


/*********************************************************************
NAME       : ~CScene
DESCRIPTION: De Constructor.
PARAMETER  : NONE
RETURN     : NONE
EXCEPTION  : NONE.
*********************************************************************/

CScene::~CScene()
{
	for (int i = 0; i < m_iShapeCount; i++)
	{
		delete m_objShapes[i];
	}
}




/*********************************************************************
NAME       : TestRayForClosest
DESCRIPTION: Test the given ray for intersections against the objects
			 in the scene and returns the closest object found.
PARAMETER  : ray	:	The ray to test for.
RETURN     : IntersectionInfo	: Information regarding the intersection.
EXCEPTION  : NONE.
*********************************************************************/

CIntersectionInfo CScene::TestRayForClosest(CRay ray)
{
	CPoint3D			ptOfIntersection;
	CColor				colorAtPoint;
	CVector				vecNormal;
	CShape*				pShape = 0;
	CTexCoords			texCoords;
	EIntersectionType	eType = ENTRY;
	
	CIntersectionInfo objHitInfoCurrent, objHitInfoClosest;

	int idForDebug;

	/**********************************************************************
	STRATEGY:
	1. Initialize all the properties using the environment.
	2. Initialize objHitInfo with the default properties, ie the environemn
	3. Test individual objects.
	**********************************************************************/

	// 1.
	ptOfIntersection	= m_objEnvironment.GetPosition();
	colorAtPoint		= m_objEnvironment.GetObjectColor();
	vecNormal			= m_objEnvironment.GetNormalAt(CPoint3D());
	pShape				= (CShape*) &m_objEnvironment;
	texCoords			= CTexCoords(0.0f, 0.0f);



	// 2.
	objHitInfoClosest = CIntersectionInfo (ptOfIntersection, 
										vecNormal, 
											colorAtPoint, 
												pShape,
													ray.Direction(),
														texCoords,
															eType);
	
	// 3.
	for (int i = 0; i < m_iShapeCount; i++)
	{
		idForDebug = i;
		
		/***************************************************************
		Loop Logic:
		This loop iterates through all the shapes in the scene graph.

		3.1. Get the point of intesectio with the object
		3.2. If the point is at infinity, dont bother, we have to use
			 the environment object anyway, just skip to the next object.
		3.3. If the intersection is not at infinity then check whether this
			 new object is closer or the object that we already have stored.
			 If the previous object is closer then just move on or get inside
			 and copy the new details.
		***************************************************************/

		// 3.1.
		objHitInfoCurrent	= m_objShapes[i]->GetIntersection(ray);

		// 3.2.
		if ( objHitInfoCurrent.GetPointOfIntersection().AtInfinity())
		{
			continue;
		}

		// 3.3.
		if ( objHitInfoCurrent.GetPointOfIntersection().IsCloser(ray.Origin(), objHitInfoClosest.GetPointOfIntersection())
													&& 
			CPoint3D::GetDistance(objHitInfoCurrent.GetPointOfIntersection(), ray.Origin()) > MARGIN_OF_ERROR)
		{
			/*****************************************************************
			We are in here, that means the current point is closer to the ray
			origin than the 'closest'. So copy the values in order to make teh
			current point the new closest point.

			LOGIC:
			3.3.1. Cache all values we need.
			3.3.2. Set teh new values into the hitInfo object.
			*****************************************************************/

			// 3.3.1.
			ptOfIntersection = objHitInfoCurrent.GetPointOfIntersection();
			colorAtPoint= objHitInfoCurrent.GetColor();
			vecNormal	= objHitInfoCurrent.GetNormal();
			texCoords	= objHitInfoCurrent.GetTextureCoordinates();
			pShape		= (CShape*)m_objShapes[i];
			eType		= isEntry(ray.Direction(), vecNormal)? ENTRY : EXIT;

			// 3.3.2.
			objHitInfoClosest = CIntersectionInfo (ptOfIntersection, vecNormal, colorAtPoint, pShape, ray.Direction(),texCoords, eType);
		}
	}
	

	return objHitInfoClosest;
}



/*********************************************************************
NAME       : isEntry
DESCRIPTION: Returns true if the incoming vector is entering the surface (i.e.
			 the normal and the incoming vector are in the OPP direction)
			 and false if the incoming vector is leaving the surface ( i.e.
			 the incoming vector and the surface normal are in teh SAME 
			 direction)
PARAMETER  : vecIncoming	: the Incoming vector.
			 vecNormal		: the normal to the surface.

RETURN     : bool	: true if entering.
EXCEPTION  : NONE.
*********************************************************************/

bool CScene::isEntry(CVector vecIncoming, CVector vecNormal)
{
	float dotProduct;

	dotProduct = vecIncoming.DotProduct(vecNormal);

	if (dotProduct < 0)
		return true;

	return false;
}

CCamera* CScene::GetCamera()
{
	return m_objCameras[0];
}



/*********************************************************************
NAME       : GetNumLights
DESCRIPTION: Returns the number of lights in the scene
PARAMETER  : NONE
RETURN     : Number of lights as an integer.
EXCEPTION  : NONE.
*********************************************************************/

int	CScene::GetNumLights()
{
	return m_iLightCount;
}



/*********************************************************************
NAME       : GetLights
DESCRIPTION: Gets an array of CLight pointers
PARAMETER  : NONE
RETURN     : Array of light pointers
EXCEPTION  : NONE.
*********************************************************************/

CLight** CScene::GetLights()
{
	return m_objLights;
}



/*********************************************************************
NAME       : IsUnobstructed
DESCRIPTION: Checks if anything lies in the path of the ray. Returns true
			 if nothing lies there. (The margin of error is used here)
PARAMETER  : rayToTest	: the ray to test for intersections.
RETURN     : bool
EXCEPTION  : NONE.
*********************************************************************/

bool CScene::IsUnobstructed		(CRay rayToTest)
{
	/***************************************************************
	STRATEGY:
	1. Set the default return value to true.
	2. Loop through all the objects to see if any object intersects
	   the ray before it reaches the destination point.
	3. Return the value obtained.
	***************************************************************/

	// 1.
	bool IsUnobstructed = true;
	
	// 2.
	for ( int i = 0; i < m_iShapeCount; i++ )
	{
		/***********************************************************
		LOOP LOGIC:
		2.1. Get the point of intersection with the object.
		2.2. See if the point of intersection lies at infinity, if not
		     then proceed further.
		***********************************************************/

		// 2.1.
		CIntersectionInfo hitInfo = m_objShapes[i]->GetIntersection(rayToTest);

		// 2.2.
		if (! hitInfo.GetPointOfIntersection().AtInfinity() ) 
		{
			/***********************************************************
			Logic:
			2.2.1. Compare the distance between this point and the origin
				   of the ray and the magnitude of the ray. (Use margin-
				   of-error to advantage of lighting).
			***********************************************************/
			if (CPoint3D::GetDistance(hitInfo.GetPointOfIntersection(),rayToTest.Destination())  + MARGIN_OF_ERROR < rayToTest.Magnitude())
			{
				IsUnobstructed = false;
				break;
			}
		}
	}

	
	// 3.
	return IsUnobstructed;
}





/***********************************************************************************************************************
											OBJECT DESCRIPTIONS.

								This part will actually be read in from a file.

***********************************************************************************************************************/

/**************************************************
Creates teh checkerboard plane for the floor.
**************************************************/

void CScene::CreateFloor()
{
	CShader		*pShader = 0;
	CTextureMap *pDesign = 0;

	// The plane Object.
	m_objShapes[m_iShapeCount]	= new CPlane( CPoint3D (0.0f,0.0f, 0.0f), g_objRed, 50,50, CVector (0.0f, 1.0f, 0.0f), CVector(0,0,1)); 
	
	
	// The checkerboard texture.
//	pDesign = new CCheckerBoard (CColor (0.1f,0.1f, 0.9f), CColor (0,0,0.4f), CColor (1,1,1), 
//									CColor (1.0f,1.0f, 1.0f), CColor (0.2f,0.2f,0.2f), CColor (1,1,1),
//										20);

	pDesign = new CFancyTile (CColor(0.3f, 0.3f, 0.3f), CColor (0.1f, 0.1f, 0.1f), CColor (0.3f, 0.3f, 0.3f),
									CColor(0.9f, 0.9f, 0.9f), CColor (0.3f, 0.3f, 0.3f), CColor (1.0f, 1.0f, 1.0f),
										CColor(0.3f, 0.3f, 1.0f), CColor (0.1f, 0.1f, 0.3f), CColor (0.8f, 0.8f, 1.0f),
											20, 0.02f, 0.2f);

	pShader	 = new CPhong(g_objRed, CColor(0.1f, 0.0f, 0.0f), CColor(1.0f, 1.0f, 1.0f), 0.7f, 5.0f, 0.8f, 0.2f, 0.0f, true);
	pShader->AssignTexture(pDesign);

	m_objShapes[m_iShapeCount]->AssignShader(pShader);
	m_iShapeCount++;
}



/**************************************************
Creates Reflective sphere.
**************************************************/

void CScene::CreateReflectiveBall()
{
	CShader *pShader = 0;
	// The reflective Sphere
	m_objShapes[m_iShapeCount]	= new CSphere( CPoint3D (0.0f,3.0f,0.0f), g_objGreen, 3.0f );
	
	pShader						= new CPhong(CColor(0.0f,0.0f,1.0f), CColor(0.0f, 0.1f, 0.0f), CColor(1.0f, 1.0f, 1.0f), 10.1f, 0.3f, 0.2f, 0.8f, 0.0f, false);
	m_objShapes[m_iShapeCount]->AssignShader(pShader);
	
	m_iShapeCount++;
}



/**************************************************
Creates the Refractive sphere.
**************************************************/

void CScene::CreateCrystalBall()
{
	CShader *pShader = 0;

	// The refractive sphere
	pShader						= new CPhong(g_objYellow, CColor(0.0f, 0.0f, 0.1f), CColor(1.0f, 1.0f, 1.0f), 0.8f, 16.3f, 0.1f, 0.0f, 0.9f, false);
	
	m_objShapes[m_iShapeCount]	= new CSphere( CPoint3D (-10.0f,1.5f,-10.0f), g_objBlue , 1.5f);
	m_objShapes[m_iShapeCount]->AssignShader(pShader);
	m_iShapeCount++;

	m_objShapes[m_iShapeCount]	= new CSphere( CPoint3D (10.0f,1.5f,-10.0f), g_objBlue , 1.5f);
	m_objShapes[m_iShapeCount]->AssignShader(pShader);
	m_iShapeCount++;

	m_objShapes[m_iShapeCount]	= new CSphere( CPoint3D (0.0f,1.5f,-20.0f), g_objBlue , 1.5f);
	m_objShapes[m_iShapeCount]->AssignShader(pShader);
	m_iShapeCount++;

}




/**************************************************
Creates a triangle for the scene.
**************************************************/

void CScene::CreateTriangle()
{
	CShader *pShader = 0;
	
	CPoint3D verts[3];
	verts[0] = CPoint3D( 0,0,20);
	verts[1] = CPoint3D( 4,0,17);
	verts[2] = CPoint3D( 2,2,15);

	m_objShapes[m_iShapeCount] = new CTriangle( CPoint3D (0, 0, 0), CColor (1.0f, 0,0), verts);
	
	pShader						= new CPhong(CColor(1.0f,0.0f,0.0f), CColor(0.0f, 0.1f, 0.0f), CColor(1.0f, 1.0f, 1.0f), 0.7f, 65.0f, 1.0f, 0.0f, 0.0f, false);
	m_objShapes[m_iShapeCount]->AssignShader(pShader);

	m_iShapeCount ++;
}



/**************************************************
Creates a mesh for the scene.
**************************************************/

void CScene::CreateMesh()
{
	CShader *pShader=0;

	// The mesh 
	CPoint3D verts[] = {	CPoint3D(0,0,0), CPoint3D(1,0,0), CPoint3D(-1,0,1), CPoint3D(0,0,1), CPoint3D(1,0,1), CPoint3D(-1, 0, 2), CPoint3D(0,0,2),CPoint3D(1,0,2), 
						CPoint3D(0,1,0), CPoint3D(1,1,0), CPoint3D(-1,1,1), CPoint3D(0,1,1), CPoint3D(1,1,1), CPoint3D(-1, 1, 2), CPoint3D(0,1,2),CPoint3D(1,1,2)};

	unsigned int faces[][3] = { {8,9,11}, {9, 12,11}, {10,11,13}, {13,11,14},{14,11,15},{15,11,12},
								{0,1,8}, {8,1,9}, {1,4,9},{9,4,12},{4,7,12},{12,7,15}, {7,6,15},{15,6,14},{6,5,14},{14,5,13},
									{5,2,13},{13,2,10},{2,3,10},{10,3,11},{3,0,11},{11,0,8},
								{3,1,0},{3,4,1},{3,7,4},{3,6,7},{3,5,6},{3,2,5}};

	int faceCount = 6;

	m_objShapes[m_iShapeCount] = new CMesh( CPoint3D (0, 0, 0), CColor (1.0f, 0,0), verts, faces, 16, faceCount);

	pShader		= new CPhong(CColor(1.0f,0.0f,0.0f), CColor(0.0f, 0.1f, 0.0f), CColor(1.0f, 1.0f, 1.0f), 0.7f, 65.0f, 1.0f, 0.0f, 0.0f, false);
	m_objShapes[m_iShapeCount]->AssignShader(pShader);

	m_iShapeCount ++;
}



/**************************************************
Creates the lights.
**************************************************/

void CScene::CreateLights()
{
	m_objLights[m_iLightCount]	= new CLight( CColor(1.0f, 0.0f, 0.0f), 1.0f, CPoint3D (6.0f, 2.5f, -10.0f));
	m_iLightCount++;

	m_objLights[m_iLightCount]	= new CLight( CColor(0.0f, 0.0f, 1.0f), 1.0f, CPoint3D (4.0f, 2.5f, -13.0f));
	m_iLightCount++;

	m_objLights[m_iLightCount]	= new CLight( CColor(0.0f, 1.0f, 0.0f), 1.0f, CPoint3D (8.0f, 2.5f, -13.0f));
	m_iLightCount++;
}



/**************************************************
Creates the camera.
**************************************************/

void CScene::CreateCamera()
{
		// Camera
	m_objCameras[m_iCamCount]	= new CCamera ( CPoint3D (10.0f, 10.0f, -37.0f), // Camera pos
													CVector (0.0f, 1.0f, 0.0f), // Up Vector
														CVector (-1.0f, -1.0f, 2.5f),  // Look-at vector
															50.0f,						 // Angle of view along y axis
																1.0f,						// film plane distance
																	(480.0f / 640.0f));			// Aspect Ratio
	m_iCamCount++;

	for (int i = 0; i < m_iCamCount; i++)
	{
		m_objCameras[i]->Initialize();
	}
}
