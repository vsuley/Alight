// Color.cpp: implementation of the CColor class.
//
//////////////////////////////////////////////////////////////////////

#include "Color.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CColor::CColor()
{

}

CColor::~CColor()
{

}



/*********************************************************************
NAME       : CColor
DESCRIPTION: parameterized constructor for CColor object
PARAMETER  : r	: the red component of the color
             g  : the green component of the color
			 b  : the blue component of the color
RETURN     : NONE
EXCEPTION  : NONE.
*********************************************************************/

CColor::CColor	(float r, float g, float b)
{
	this->fRed		= r;
	this->fGreen	= g;
	this->fBlue		= b;
}


/*********************************************************************
NAME       : SetColor
DESCRIPTION: Sets the value of the rgb triplet
PARAMETER  : r	: the red component of the color
             g  : the green component of the color
			 b  : the blue component of the color
RETURN     : NONE
EXCEPTION  : NONE.
*********************************************************************/

void CColor::SetColor (float r, float g, float b)
{
	this->fRed		= r;
	this->fGreen	= g;
	this->fBlue		= b;
}




/*********************************************************************
NAME       : GetRed	
DESCRIPTION: Gets the red component of the color
PARAMETER  : NONE
RETURN     : The red component of the color
EXCEPTION  : NONE.
*********************************************************************/

float	CColor::GetRed	()
{
	return fRed;
}


/*********************************************************************
NAME       : GetGreen
DESCRIPTION: Fetches the green component of the color
PARAMETER  : NONE
RETURN     : The green component of the color
EXCEPTION  : NONE.
*********************************************************************/

float	CColor::GetGreen()
{
	return fGreen;
}


/*********************************************************************
NAME       : GetBlue
DESCRIPTION: Fetches the blue component of the color
PARAMETER  : NONE
RETURN     : The blue component
EXCEPTION  : NONE.
*********************************************************************/

float	CColor::GetBlue	()
{
	return fBlue;
}
	


/*********************************************************************
NAME       : operator *
DESCRIPTION: Multiplies the color with an intensity. ie, scales it.
PARAMETER  : intensity	:	The factor to scale the color by. max 1.
RETURN     : The resultant color
EXCEPTION  : NONE.
*********************************************************************/

CColor	CColor::operator *	(float intensity)
{
	CColor result;

	if (intensity > 1)
	{
		intensity = 1;
	}
	
	if (intensity < 0)
	{
		intensity = 0;
	}

	result.fBlue = this->fBlue	* intensity;
	result.fGreen= this->fGreen	* intensity;
	result.fRed	 = this->fRed	* intensity;

	return result;
}



/*********************************************************************
NAME       : operator * (CColor)
DESCRIPTION: Multiplies the color with another color
PARAMETER  : col2	:	The color to multiply with
RETURN     : The resultant color
EXCEPTION  : NONE.
*********************************************************************/

CColor	CColor::operator *	(CColor col2)
{
	CColor result;

	result.fBlue = (float)(int((this->fBlue	* col2.fBlue)  * 1000.0f))	/ 1000.0f;
	result.fGreen= (float)(int((this->fGreen* col2.fGreen) * 1000.0f))	/ 1000.0f;
	result.fRed	 = (float)(int((this->fRed	* col2.fRed)   * 1000.0f))	/ 1000.0f;

	return result;
}




/*********************************************************************
NAME       : operator +=
DESCRIPTION: Adds a given color to itself.
PARAMETER  : col2	: the color to add.
RETURN     : void
EXCEPTION  : NONE.
*********************************************************************/

void	CColor::operator += (CColor col2)
{
	this->fBlue	+= col2.fBlue;
	this->fGreen+= col2.fGreen;
	this->fRed	+= col2.fRed;

	if(fBlue > 1) fBlue = 1;
	if(fGreen> 1) fGreen= 1;
	if(fRed	 > 1) fRed	= 1;

	if(fBlue < 0) fBlue = 0;
	if(fGreen< 0) fGreen= 0;
	if(fRed	 < 0) fRed	= 0;

}


CColor CColor::Average (CColor *colors, int count)
{
	float avgRed, avgGreen, avgBlue;

	avgRed = avgGreen = avgBlue = 0.0f;

	/******************************************************************
	NOTE:
	The purpose of this function is to serve as a utility to calculate
	the average of many colors. One of the most obvious uses is anti-
	aliasing. Right now it just computes a simple mean, but it might
	use a more advanced algorithm later on.
	******************************************************************/

	for (int i = 0; i < count; i ++ ) {

		avgRed		+= colors[i].GetRed();
		avgGreen	+= colors[i].GetGreen();
		avgBlue		+= colors[i].GetBlue();
	}

	return CColor (avgRed/(float)count, avgGreen/(float)count, avgBlue/(float)count);
}


bool CColor::operator != (CColor col2)
{
	if (this->fBlue != col2.fBlue || this->fGreen != col2.fGreen || this->fRed != col2.fRed)
		return true;
	
	return false;
}
