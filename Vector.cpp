
// Vector.cpp: implementation of the CVector class.
//
//////////////////////////////////////////////////////////////////////

# include "Vector.h"
# include "Math.h"
# include "Point3D.h"
# include <iostream>

using namespace std;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CVector::CVector()
{

}

CVector::~CVector()
{

}




/*********************************************************************
NAME       : CVector
DESCRIPTION: Parameterized Constructor
PARAMETER  : dx	: the x component of the vector
			 dy	: the y component of the vector
			 dz	: the z component of the vector
RETURN     : NONE
EXCEPTION  : NONE.
*********************************************************************/

CVector::CVector (float dx, float dy, float dz)
{
	this->m_fdx = dx;
	this->m_fdy = dy;
	this->m_fdz = dz;
}



/*********************************************************************
NAME       : CVector
DESCRIPTION: Copying a Point3D object into ourselves.
PARAMETER  : ray1	: The ray object to be copied
RETURN     : NONE
EXCEPTION  : NONE.
*********************************************************************/

CVector::CVector(CPoint3D ptRay1)
{
	this->m_fdx = ptRay1.GetX();
	this->m_fdy = ptRay1.GetY();
	this->m_fdz = ptRay1.GetZ();
}
	


/*********************************************************************
NAME       : operator=
DESCRIPTION: Assignment operator
PARAMETER  : point: the Point3D whose values we have to copy
RETURN     : A ref to this.
EXCEPTION  : NONE.
*********************************************************************/
CVector& CVector::operator= (const CPoint3D& point)
{
	this->m_fdx = point.GetX();
	this->m_fdy = point.GetY();
	this->m_fdz = point.GetZ();
    
    return *this;
}


/*********************************************************************
NAME       : SetVector
DESCRIPTION: This function initializes the vector
PARAMETER  : dx	: the x component of the vector
			 dy	: the y component of the vector
			 dz	: the z component of the vector
RETURN     : void
EXCEPTION  : NONE.
*********************************************************************/

void	CVector::SetVector	(float dx, float dy, float dz)
{
	this->m_fdx = dx;
	this->m_fdy = dy;
	this->m_fdz = dz;
}
	



/*********************************************************************
NAME       : Magnitude
DESCRIPTION: This function returns the magnitude of the vector
PARAMETER  : NONE
RETURN     : float
EXCEPTION  : NONE.
*********************************************************************/

float CVector::Magnitude() const
{
	return (float) sqrt ( m_fdx * m_fdx + m_fdy * m_fdy + m_fdz * m_fdz);
}


	


/*********************************************************************
NAME       : Normalize
DESCRIPTION: This function normalizes the vector
PARAMETER  : NONE
RETURN     : float
EXCEPTION  : NONE.
*********************************************************************/

CVector& CVector::Normalize()
{
	float fMag = Magnitude();

	if (fMag)
	{
		m_fdx /= fMag;
		m_fdy /= fMag;
		m_fdz /= fMag;
	}
    
    return *this;
}


	


/*********************************************************************
NAME       : XComponent
DESCRIPTION: Returns the X component of the vector
PARAMETER  : NONE
RETURN     : The X component of the vector in floating point
EXCEPTION  : NONE.
*********************************************************************/

float	CVector::XComponent	() const
{
	return m_fdx;
}
	


/*********************************************************************
NAME       : YComponent
DESCRIPTION: Returns the Y component of the vector
PARAMETER  : NONE
RETURN     : The Y component of the vector in floating point
EXCEPTION  : NONE.
*********************************************************************/

float	CVector::YComponent	() const
{
	return m_fdy;
}
	

/*********************************************************************
NAME       : ZComponent
DESCRIPTION: Returns the Z component of the vector
PARAMETER  : NONE
RETURN     : The Z component of the vector in floating point
EXCEPTION  : NONE.
*********************************************************************/

float	CVector::ZComponent	() const
{
	return m_fdz;
}



/*********************************************************************
NAME       : DotProduct	
DESCRIPTION: Computes the dot product of this vector with the specified
			 vector
PARAMETER  : The vector to dot this with.
RETURN     : The dot product of the two vectors.
EXCEPTION  : NONE.
*********************************************************************/

float CVector::DotProduct	(CVector vector1)
{
	float result;
	
	try {
		result = m_fdx * vector1.m_fdx + m_fdy * vector1.m_fdy + m_fdz * vector1.m_fdz;
	
	} catch (...) {
		cout << "Exception";
	}
	
	return result;
}





/*********************************************************************
NAME       : operator * (float)
DESCRIPTION: Scales the vector by the given factor
PARAMETER  : The scaling factor
RETURN     : The scaled vector
EXCEPTION  : NONE.
*********************************************************************/

CVector CVector::operator * (float fScale)
{
    CVector result;
    
	result.m_fdx = fScale*m_fdx;
    result.m_fdy = fScale*m_fdy;
    result.m_fdz = fScale*m_fdz;
    
    return result;
}



/*********************************************************************
NAME       : operator - (CVector)
DESCRIPTION: subtracts the given vector from this one.
PARAMETER  : The vector to be subtracted
RETURN     : The resultant vector
EXCEPTION  : NONE.
*********************************************************************/

CVector CVector::operator - (const CVector& that)
{
    CVector result;
    
    result.m_fdx = m_fdx - that.m_fdx;
    result.m_fdy = m_fdy - that.m_fdy;
    result.m_fdz = m_fdz - that.m_fdz;

    return result;
}

/*********************************************************************
NAME       : operator + (CVector)
DESCRIPTION: Adds itself and the given vector into a new vector.
PARAMETER  : The vector to be added
RETURN     : The resultant vector.
EXCEPTION  : NONE.
*********************************************************************/

CVector CVector::operator+ (const CVector& that)
{
    CVector result;
    
    result.m_fdx = m_fdx + that.m_fdx;
    result.m_fdy = m_fdy + that.m_fdy;
    result.m_fdz = m_fdz + that.m_fdz;
    
    return result;
}


/*********************************************************************
NAME       : CrossProduct
DESCRIPTION: Computes the cross product of this x that. Please note the
			 order.
PARAMETER  : The vector to be multiplied with
RETURN     : The resultant vector
EXCEPTION  : NONE.
*********************************************************************/

CVector CVector::CrossProduct(CVector that)
{
	CVector vecResult;

	vecResult.m_fdx = (this->m_fdy * that.m_fdz) - (this->m_fdz * that.m_fdy);
	vecResult.m_fdy = (this->m_fdz * that.m_fdx) - (this->m_fdx * that.m_fdz);
	vecResult.m_fdz = (this->m_fdx * that.m_fdy) - (this->m_fdy * that.m_fdx);

	return vecResult;
}



/*********************************************************************
NAME       : GetOrthoAlong	
DESCRIPTION: This function computes a vector perfectly orthogonal to this
		     along the given direction.
PARAMETER  : The approximate direction
RETURN     : The resultant vector
EXCEPTION  : NONE.
*********************************************************************/

CVector	CVector::GetOrthoAlong	(CVector approxDirection)
{
	CVector Ortho;
	CVector temp;

	temp = approxDirection.CrossProduct(*this);

	Ortho = this->CrossProduct(temp);

	return Ortho;
}
