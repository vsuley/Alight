// Mesh.h: interface for the CMesh class.
//
//////////////////////////////////////////////////////////////////////
# ifndef _MESH_H
# define _MESH_H

# include "Shape.h"
# include "Triangle.h"

class CMesh : public CShape  
{
public:
	
	CMesh	(CPoint3D pos, CColor col, CPoint3D *pptVertices, CVector *pvecNormals, unsigned int *ppiFaces[3], int iVertexCount, int iFaceCount);
	CMesh	(CPoint3D pos, CColor col, CPoint3D *pptVertices, unsigned int ppiFaces[][3], int iVertexCount, int iFaceCount);
	CMesh	(CMesh &mesh1);

	// Object interface
	CIntersectionInfo GetIntersection	(CRay ray);

	CVector		GetNormalAt		(CPoint3D pt);
	CColor		ShadePoint		(CIntersectionInfo hitInfo);
	CTexCoords	GetTexCoords	(CPoint3D ptOfIntersection);
	
	// Destruction
	virtual ~CMesh();

protected:
	NORMAL_MODE m_eNormalMode;

	CTriangle	*m_pTriangles;
	int			m_iTriangleCount;
};

# endif