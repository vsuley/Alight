// Mesh.cpp: implementation of the CMesh class.
//
//////////////////////////////////////////////////////////////////////

#include "Mesh.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

	
/*********************************************************************
NAME       : CMesh
DESCRIPTION: Parameterized constructor (use only for VERTEX NORMAL mode)
PARAMETER  : pos	: The position of the mesh in space.
			 col	: The color of the mesh.
			 pptVertices	: The array of vertices.
			 pvecNormals	: The array of normals, one for each vertex.
			 ppiFaces		: A 2-D array of faces.
			 iVertexCount	: The number of vertices in the mesh.
			 iFaceCount		: The number of faces in the mesh.


RETURN     : NONE
EXCEPTION  : NONE.
*********************************************************************/

CMesh::CMesh	(CPoint3D pos, CColor col, CPoint3D *pptVertices, CVector *pvecNormals, unsigned int *ppiFaces[3], int iVertexCount, int iFaceCount) : CShape (pos, col)
{
	/*****************************************************************
	STRATEGY:
	1. The fact that we have come into THIS particular constructor 
	   means that this mesh is in vertex normal mode...so set it so.
	2. Set the triangle count equal to the face count.
	3. Create the array of triangles.
	4. Initialize all triangles.
	*****************************************************************/

	// 1.
	this->m_eNormalMode = VERTEX_NORMAL;
	
	// 2.
	this->m_iTriangleCount = iFaceCount;
	
	// 3.
	m_pTriangles = new CTriangle[m_iTriangleCount];

	// 4.
	for (int i = 0; i < iFaceCount; i++ ) {

		CPoint3D pptVertices[3];
		CVector	 pvecNormals[3];
		
		/************************************************************
		STRATEGY:
		4.1. Intialize the vertex array.
		4.2. Initialize the normals array.
		4.3. Intialize the current triangle.
		************************************************************/

		// 4.1. 
		pptVertices[0] = pptVertices[ ppiFaces[i][0] ];
		pptVertices[1] = pptVertices[ ppiFaces[i][1] ];
		pptVertices[2] = pptVertices[ ppiFaces[i][2] ];

		// 4.2.
		pvecNormals[0] = pvecNormals [ ppiFaces[i][0] ];
		pvecNormals[1] = pvecNormals [ ppiFaces[i][1] ];
		pvecNormals[2] = pvecNormals [ ppiFaces[i][2] ];


		// 4.3.
		m_pTriangles[i].Init(pos, col, pptVertices, pvecNormals);
	}
}


	
/*********************************************************************
NAME       : CMesh
DESCRIPTION: Parameterized constructor (use only for FACE NORMAL mode)
PARAMETER  : pos	: The position of the mesh in space.
			 col	: The color of the mesh.
			 pptVertices	: The array of vertices.
			 ppiFaces		: A 2-D array of faces.
			 iVertexCount	: The number of vertices in the mesh.
			 iFaceCount		: The number of faces in the mesh.


RETURN     : NONE
EXCEPTION  : NONE.
*********************************************************************/
CMesh::CMesh	(CPoint3D pos, CColor col, CPoint3D *pptVertices, unsigned int ppiFaces[][3], int iVertexCount, int iFaceCount)  : CShape (pos, col)
{
	/*****************************************************************
	STRATEGY:
	1. The fact that we have come into THIS particular constructor 
	   means that this mesh is in face normal mode...so set it so.
	2. Set the triangle count equal to the face count.
	3. Create the array of triangles.
	4. Initialize all triangles.
	*****************************************************************/

	// 1.
	this->m_eNormalMode = FACE_NORMAL;
	
	// 2.
	this->m_iTriangleCount = iFaceCount;
	
	// 3.
	m_pTriangles = new CTriangle[m_iTriangleCount];

	// 4.
	for (int i = 0; i < iFaceCount; i++ ) {

		CPoint3D pptCurrentVertices[3];
		
		/************************************************************
		STRATEGY:
		4.1. Intialize the vertex array.
		4.2. Intialize the current triangle.
		************************************************************/

		// 4.1. 
		pptCurrentVertices[0] = pptVertices[ ppiFaces[i][0] ];
		pptCurrentVertices[1] = pptVertices[ ppiFaces[i][1] ];
		pptCurrentVertices[2] = pptVertices[ ppiFaces[i][2] ];

		// 4.2.
		m_pTriangles[i].Init(pos, col, pptCurrentVertices);
	}
}



/*********************************************************************
NAME       : CMesh
DESCRIPTION: Copy constructor
PARAMETER  : mesh1	: The object to be copied.
RETURN     : void
EXCEPTION  : NONE.
*********************************************************************/

CMesh::CMesh	(CMesh &mesh1)
{
	this->m_eNormalMode		= mesh1.m_eNormalMode;
	this->m_iTriangleCount	= mesh1.m_iTriangleCount;
	this->m_pShader			= mesh1.m_pShader;
	this->m_ptPosition		= mesh1.m_ptPosition;
	this->m_pTriangles		= mesh1.m_pTriangles;
	this->objColor			= mesh1.objColor;
}



// Object interface

/*********************************************************************
NAME       : GetIntersection
DESCRIPTION: Computes if the given ray collides with the object and if
		     yes, then we fill in all relevant of details* and return them
			 in the intersection info object.
PARAMETER  : ray	: The ray to check for collision.
RETURN     : CIntersectionInfo
EXCEPTION  : NONE.
*********************************************************************/

CIntersectionInfo	CMesh::GetIntersection	(CRay ray)
{
	/*****************************************************************
	STRATEGY:
	1. Run a high level check (like a bounding box check) to see if the 
	   ray passes us before trying to query each triangle. This will save
	   time.
	2. If the high level check is passed, query each triangle to get the 
	   information.
	3. Return the information obtained.
	*****************************************************************/

	// 1.
	// N.Y.I.

	// 2.
	CIntersectionInfo hitInfoCurrent, hitInfoClosest;
	
	hitInfoClosest.SetPointOfIntersection(CPoint3D (0,0,0,0));

	for (int i = 0; i < m_iTriangleCount; i++ ) {
		
		/***********************************************************
		2.1. Query the current triangle and store its information
		     in the hitInfoCurrent.
		2.2. Make sure that this is not infinity.
		2.3. Check if the current hit is closer than the last closest
			 hit we have recorded. If not then continue.
		2.4. We are here that means the previous two checks passed. now
			 Put fresh details into the hitInfoClosest.
		***********************************************************/

		// 2.1.
		hitInfoCurrent = m_pTriangles[i].GetIntersection(ray);

		// 2.2.
		if (hitInfoCurrent.GetPointOfIntersection().AtInfinity() ) {
			continue;
		}

		// 2.3.
		if (! hitInfoCurrent.GetPointOfIntersection().IsCloser(ray.Origin(), hitInfoClosest.GetPointOfIntersection()))
		{
			continue;
		}

		// 2.4.
		hitInfoClosest = hitInfoCurrent;

	}

	// 3.
	return hitInfoClosest;
}




/*********************************************************************
NAME       : ShadePoint
DESCRIPTION: This function triggers the shader into action and returns
			 the color which the represents the given pixel best.
PARAMETER  : hitInfo	: The information for the point to be shaded.
RETURN     : CColor
EXCEPTION  : NONE
*********************************************************************/

CColor		CMesh::ShadePoint		(CIntersectionInfo hitInfo)
{
	if (m_pShader == 0) {

		return objColor;
	}

	return m_pShader->ShadePoint(hitInfo);
}




/*********************************************************************
NAME       : GetTexCoords
DESCRIPTION: Returns the texture coordinates at the point
PARAMETER  : ptOfIntersection	: The point to be queried.
RETURN     : CTexCoords.
EXCEPTION  : NONE
*********************************************************************/

CTexCoords	CMesh::GetTexCoords	(CPoint3D ptOfIntersection)
{
	return CTexCoords (0,0);
}



CMesh::~CMesh()
{

}
