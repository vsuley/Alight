// IntersectionInfo.h: interface for the CIntersectionInfo class.
//
//////////////////////////////////////////////////////////////////////

# ifndef _INTERSECTIONINFO_H
# define _INTERSECTIONINFO_H

# include "Point3D.h"
# include "TexCoords.h"
# include "Vector.h"
# include "Color.h"
# include "Shape.h"

class CShape;

typedef enum {
	ENTRY,
	EXIT
}EIntersectionType;

class CIntersectionInfo  
{
public:
	
	// Object Construction
	CIntersectionInfo	();
	CIntersectionInfo	(const CIntersectionInfo& obj1);
	
	CIntersectionInfo	(CPoint3D			pt, 
						 CVector			normal, 
						 CColor				col, 
						 CShape*			pShape, 
						 CVector			vecIncoming, 
						 CTexCoords			texPt, 
						 EIntersectionType	eType
						);

	// Object destruction
	virtual ~CIntersectionInfo();
    
    // assignment
    CIntersectionInfo&  operator= (const CIntersectionInfo& that);

	// Object interface
	CVector				GetNormal();
	CColor				GetColor();
	CPoint3D			GetPointOfIntersection();
	CTexCoords			GetTextureCoordinates();
	CShape*				GetShape();
	CVector				GetIncoming();
	EIntersectionType	GetIntersectionType();
	
	void	SetPointOfIntersection	(CPoint3D pt);
	void	SetNormal				(CVector vecNormal);
	void	SetColor				(CColor colObject);
	void	SetTexCoords			(CTexCoords texCoords);

protected:

	// Protected Object variables
	CPoint3D	m_ptIntersection;
	
	CVector		m_vecNormal;

	CVector		m_vecIncoming;
	
	CColor		m_colObject;

	CShape*		m_pShapeObject;
	
	CTexCoords	m_texIntersection;

	EIntersectionType m_eIntersectionType;
};

# endif