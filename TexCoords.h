// TexCoords.h: interface for the CTexCoords class.
//
//////////////////////////////////////////////////////////////////////

# ifndef _TEXCOORDS_H
# define _TEXCOORDS_H

class CTexCoords  
{
public:
	CTexCoords	();
	CTexCoords	(float fU, float fV);
	virtual	~CTexCoords();

	float getU() {return m_fU;}
	float getV() {return m_fV;}

protected:

	float m_fU;
	float m_fV;
};

# endif