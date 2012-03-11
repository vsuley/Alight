// Log.h: interface for the CLog class.
//
//////////////////////////////////////////////////////////////////////

# ifndef _LOG_H
# define _LOG_H

class CLog  
{
public:
	CLog();
	virtual ~CLog();

	void SetLogFileName (char szFileName[256]);

	void Write (char* szString);

private:

	char szFileName[256];

};

# endif