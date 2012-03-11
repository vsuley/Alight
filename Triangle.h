// Triangle.h: interface for the CTriangle class.
//
//////////////////////////////////////////////////////////////////////

# ifndef _TRIANGLE_H
# define _TRIANGLE_H

# include "Shape.h"
//# include "Vector.h"

enum NORMAL_MODE {FACE_NORMAL, VERTEX_NORMAL};

class CTriangle : public CShape  
{
public:
	
	// Object constructors
	CTriangle	();
	
	CTriangle	(CPoint3D pos, CColor col, CPoint3D pptVertices[3], CVector pvecNormals[3]);
	CTriangle	(CPoint3D pos, CColor col, CPoint3D pptVertices[3]);
	CTriangle	(CTriangle &triangle1);

	// Object interface
	CIntersectionInfo GetIntersection	(CRay ray);

    void        Init(CPoint3D pos, CColor col, CPoint3D pptVertices[3], CVector pvecNormals[3]);
    void        Init(CPoint3D pos, CColor col, CPoint3D pptVertices[3]);
	CVector		GetNormalAt		(CPoint3D pt);
	CColor		ShadePoint		(CIntersectionInfo hitInfo);
	CTexCoords	GetTexCoords	(CPoint3D ptOfIntersection);
	
	// Destruction
	virtual ~CTriangle();

protected:
	NORMAL_MODE m_eNormalMode;
	CVector		m_vecNormal;
	CVector		m_pvecNormals[3];
	CPoint3D	m_pptVertices[3];


	// protected methods.
	void	 ComputeFaceNormal	();
	CPoint3D PlaneIntersect		(CRay ray);
	bool	 inTriangle			(CPoint3D ptOfIntersection);

};

# endif