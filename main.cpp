// Visual Studio 2022 Version 17 (17.6.33829.357)
//: H:\V1\func.cpp 

/// NOTE: If you notice that there are 2 function in finding the file, it was used on other types of strings,
/// like the wide string (ends with W) which made up of wide characters, wide chsracters supports unicode 
/// code page or format, while multi byte (ends with A) supports only ANSI code page or format.

#define WIN32_LEAN_AND_MEAN // exclude useless headers
#include <windows.h>
#include <Shellapi.h>
#include <winternl.h>

namespace V1 
{
	BOOL matchesW(LPCWSTR string1, LPCWSTR string2) 
        {
		INT szStr1, szStr2, szStringCount = 0;
		szStr1 = lstrlenW(string1),
		szStr2 = lstrlenW(string2);
		
		if (szStr1 > szStr2 && szStr1 < szStr2)
			return FALSE;
		
		for (int i = 0; i < szStr2; i++)
		{
			if (string1[i] == string2[i]) szStringCount++;
		}
		
		if (szStringCount < szStr2) 
			return FALSE;
		
		return TRUE;
	}

	BOOL matchesA(LPCSTR string1, LPCSTR string2) 
        {
		INT szStr1, szStr2, szStringCount = 0;
		szStr1 = lstrlenA(string1), 
		szStr2 = lstrlenA(string2);
		
		if (szStr1 > szStr2 && szStr1 < szStr2)
			return FALSE;
		
		for (int i = 0; i < szStr2; i++)
		{
			if (string1[i] == string2[i]) szStringCount++;
		}
		
		if (szStringCount < szStr2) 
			return FALSE;
		
		return TRUE;
	}

	BOOL WINAPI CheckIfFileExistsW(LPCWSTR lPath, LPCWSTR lpFileName)
	{
		WIN32_FIND_DATAW np; BOOL success = FALSE;
		LPWSTR sd = (LPWSTR)LocalAlloc(LMEM_ZEROINIT, MAX_PATH + 1), 
			ssfile = (LPWSTR)LocalAlloc(LMEM_ZEROINIT, 512);
		
		lstrcpyW(sd, lPath);
		if (sd[(lstrlenW(sd) - 1)] != L'\\')
		{
			if (lpFileName[0] != L'\\') {
				lstrcatW(sd, L"\\");
			}
		}
		lstrcatW(sd, L"*.*");
		
		HANDLE hFile = FindFirstFileW(sd, &np);
		if (hFile == INVALID_HANDLE_VALUE)
			goto cleanup;

		while (FindNextFileW(hFile, &np)) 
		{
			ssfile = (LPWSTR)LocalAlloc(LMEM_ZEROINIT, 512);
			lstrcpyW(ssfile, np.cFileName);
			if (!lstrcmpW(np.cFileName, L".") || !lstrcmpW(np.cFileName, L"..") || np.dwFileAttributes == FILE_ATTRIBUTE_REPARSE_POINT) continue;
			if (np.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY) {
				lstrcatW(ssfile, L"\\");
				continue;
			}

			if (matchesW(ssfile, lpFileName)) 
			{
				success = TRUE;
				goto cleanup;
			}
			LocalFree(ssfile);
		}
		cleanup:
		if (ssfile) LocalFree(ssfile);
		FindClose(hFile);
		return success;
	}

	BOOL WINAPI CheckIfFileExistsA(LPCSTR lPath, LPCSTR lpFileName)
	{
		WIN32_FIND_DATAA np; BOOL success = FALSE;
		LPSTR sd = (LPSTR)LocalAlloc(LMEM_ZEROINIT, MAX_PATH + 1),
		      ssfile = (LPSTR)LocalAlloc(LMEM_ZEROINIT, 512);
		
		lstrcpyA(sd, lPath);
		if (sd[(lstrlenA(sd) - 1)] != '\\')
		{
			if (lpFileName[0] != '\\') {
				lstrcatA(sd, "\\");
			}
		}
		lstrcatA(sd, "*.*");
		
		HANDLE hFile = FindFirstFileA(sd, &np);
		if (hFile == INVALID_HANDLE_VALUE)
			goto cleanup;

		while (FindNextFileA(hFile, &np)) 
		{
			ssfile = (LPSTR)LocalAlloc(LMEM_ZEROINIT, 512);
			lstrcpyA(ssfile, np.cFileName);
			if (!lstrcmpA(np.cFileName, ".") || !lstrcmpA(np.cFileName, "..") || np.dwFileAttributes == FILE_ATTRIBUTE_REPARSE_POINT) continue;
			if (np.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY) {
				lstrcatA(ssfile, "\\");
				continue;
			}

			if (matchesA(ssfile, lpFileName))
			{
				success = TRUE;
				goto cleanup;
			}
			LocalFree(ssfile);
		}
	cleanup:
		if (ssfile) LocalFree(ssfile);
		FindClose(hFile);
		return success;
	}
}

int main() 
{
    // just use std::cout if its a console application you were using this.
    if (V1::CheckIfFileExistsA("C:\\", "test.txt"))
        MessageBoxA(0, "found!", "test.txt", MB_OK | MB_ICONINFORMATION);
    else 
        MessageBoxA(0, "not found...", "test.txt", MB_OK | MB_ICONERROR);
    return 0;
}
