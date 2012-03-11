// Shape.h: interface for the CShape class.
//
//////////////////////////////////////////////////////////////////////

# ifndef _SHAPE_H
# define _SHAPE_H

# include "OnscreenObject.h"
# include "Color.h"
# include "Ray.h"
# include "Point3D.h"
# include "Shader.h"
# include "Vector.h"


// The include files
class CIntersectionInfo;
class CShader;

class CShape  : public COnScreenObject
{
public:
	
	// Constructors:
	CShape	();
	CShape	(CPoint3D pos, CColor col);
	
	// Interface
	virtual	void	SetObjectColor	(CColor col);
	virtual CColor	GetObjectColor	();
	virtual	void	AssignShader	(CShader* shader);

	// Pure virtual Functions
	virtual CIntersectionInfo GetIntersection	(CRay) = 0;
	virtual	CColor		ShadePoint		(CIntersectionInfo objHitInfo) = 0;
	virtual CTexCoords	GetTexCoords	(CPoint3D ptOfIntersection) = 0;	

	// Object destructor
	virtual ~CShape();

protected:
	
	CColor		objColor;
	CShader*	m_pShader;
};

# endif