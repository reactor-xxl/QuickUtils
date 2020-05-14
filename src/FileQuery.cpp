#pragma once


#include "FileQuery.hpp"

/*
	BOOL GetFileTime(
		HANDLE     hFile,
		LPFILETIME lpCreationTime,
		LPFILETIME lpLastAccessTime,
		LPFILETIME lpLastWriteTime
	);

HANDLE CreateFileW(
	LPCSTR                lpFileName,
	DWORD                 dwDesiredAccess,
	DWORD                 dwShareMode,
	LPSECURITY_ATTRIBUTES lpSecurityAttributes,
	DWORD                 dwCreationDisposition,
	DWORD                 dwFlagsAndAttributes,
	HANDLE                hTemplateFile
);

GENERIC_READ 	Specifies read access to the object. Data can be read from the file and the file pointer can be moved. Combine with GENERIC_WRITE for read-write access.
GENERIC_WRITE

*/
FileQuery::FileQuery( const Path& path ) : m_path{ path } { ; }


bool FileQuery::getTimes()
{
	const constexpr size_t SIMPLE_QUERY = 0;
	/* as opposed to GENERIC_READ or GENERIC_WRITE */

	Windows::HANDLE		fileHandle = { nullptr };

	fileHandle = Windows::CreateFileW(
		/*  LPCSTR                */	m_path.c_str(),
		/*  DWORD                 */	SIMPLE_QUERY,	/* access type 0 */
		/*  DWORD                 */	0,				/* share mode */
		/*  LPSECURITY_ATTRIBUTES */	nullptr,		/* Security attributes */
		/*  DWORD                 */	OPEN_EXISTING,	/* creation disposition */
		/*  DWORD                 */	FILE_ATTRIBUTE_NORMAL, /* flags and attributes, N/A for reading? */
		/*  HANDLE                */	nullptr /* handle to a Template File */
	);

	if ( !fileHandle )
		return false;

	Windows::FILETIME	ft_creation;
	Windows::FILETIME	ft_lastAccess;
	Windows::FILETIME	ft_modification;

	bool result = Windows::GetFileTime(
		fileHandle,
		&ft_creation,
		&ft_lastAccess,
		&ft_modification
	);

	Windows::CloseHandle( fileHandle );
	fileHandle = nullptr;

	if( !result )
		return false;


	Windows::SYSTEMTIME	sysTime;

	result = Windows::FileTimeToSystemTime(
		&ft_creation,
		&sysTime
	);


}

Windows::FILETIME 
BOOL FileTimeToSystemTime(
  const FILETIME *lpFileTime,
  LPSYSTEMTIME   lpSystemTime
);


}




void timeThing(const Path& path)
{

	HANDLE fileHandle;


CloseHandle( fileHandle );

}

