#pragma once


#include "main.hpp"
namespace Windows{
#include <Windows.h>
}
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

class FileQuery
{
public:
	FileQuery(const Path& path);
	~FileQuery() = default;
	void getTimes();

	Path		m_path;
//DWORD GetLastError();
};

void timeThing(const Path& path)
{

const constexpr size_t SIMPLE_QUERY = 0;
/* as opposed to GENERIC_READ or GENERIC_WRITE */
	HANDLE fileHandle;

fileHandle =  CreateFileW(
/*  LPCSTR                */	path.c_str(),
/*  DWORD                 */	SIMPLE_QUERY,	/* access type 0 */
/*  DWORD                 */	0,				/* share mode */
/*  LPSECURITY_ATTRIBUTES */	nullptr,		/* Security attributes */
/*  DWORD                 */	OPEN_EXISTING,	/* creation disposition */
/*  DWORD                 */	FILE_ATTRIBUTE_NORMAL, /* flags and attributes, N/A for reading? */
/*  HANDLE                */	nullptr /* handle to a Template File */
);


CloseHandle( fileHandle );

}

