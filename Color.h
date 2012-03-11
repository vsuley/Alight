// Color.h: interface for the CColor class.
//
//////////////////////////////////////////////////////////////////////

# ifndef _COLOR_H
# define _COLOR_H

class CColor  
{
public:
	
	// Object Constructors
	CColor	(float r, float g, float b);
	CColor	();

	// Object destruction
	virtual ~CColor();

	// Object Interface
	void	SetColor (float r, float g, float b);

	float	GetRed	();
	float	GetGreen();
	float	GetBlue	();

	// Operators

	CColor	operator *	(float intensity);
	void	operator += (CColor col2);
	CColor	operator *  (CColor col2);
	bool	operator != (CColor col2);

	// Utilities
	static CColor Average (CColor *colors, int count);
	
private:

	float fRed;
	float fGreen;
	float fBlue;
};

# endif