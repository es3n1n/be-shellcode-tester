#include "hooks/hooks.hpp"


namespace hooks {
	int WideCharToMultiByte( UINT CodePage, DWORD dwFlags, LPCWCH lpWideCharStr, int cchWideChar, LPSTR lpMultiByteStr, int cbMultiByte, LPCCH lpDefaultChar, LPBOOL lpUsedDefaultChar ) {
		// @note: es3n1n: stupid bastian cannot handle it properly
		//  000001CA0FE58896 | 81BC04 221D0000 64776D2E | cmp dword ptr ss:[rsp+rax+1D22],2E6D7764  |
		return ::WideCharToMultiByte( CodePage, dwFlags, lpWideCharStr, lstrlenW( lpWideCharStr ), lpMultiByteStr, cbMultiByte, lpDefaultChar, lpUsedDefaultChar );
	}
}
