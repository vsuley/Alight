// Log.cpp: implementation of the CLog class.
//
//////////////////////////////////////////////////////////////////////

# include "Log.h"
# include "Exception.h"
# include <fstream>

using namespace std;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLog::CLog()
{

}

CLog::~CLog()
{

}

/*********************************************************************
NAME       : SetLogFileName
DESCRIPTION: Initializes the name of the log file.
PARAMETER  : szFileName : Character string containing log file name
RETURN     : void
EXCEPTION  : CException.
*********************************************************************/

void CLog::SetLogFileName (char szFileName[256])
{
	ofstream logFile;
	
	/********************************************************
	STRATEGY:
	1. Set the filename variable to the name that we have been
	   passed.
	2. Test that the name that we have been passed is usable.
	   If not then throw an exception.
	********************************************************/

	// 1.
	strcpy (this->szFileName, szFileName);

	// 2.
	logFile.open(this->szFileName);

	if (!logFile)
	{
		throw new CException();
	}
}



/*********************************************************************
NAME       : Write
DESCRIPTION: Writes a character string into the log file
PARAMETER  : szString : Character string to be written
RETURN     : void
EXCEPTION  : NONE.
*********************************************************************/

void CLog::Write (char* szString)
{
	ofstream logFile;
	
	/********************************************************
	STRATEGY:
	1. Open the logfile in append mode.
	2. Write into the logfile.
	3. Close the log file.
	********************************************************/

	// 1.
	logFile.open(this->szFileName, ios::out|ios::app);

	// 2.
	logFile << szString;

	// 3.
	logFile.close();

}