#pragma once
#include "util/util.hpp"


namespace hooks {
	// winapi funcs
	HMODULE GetModuleHandleA( const char* module_name );
	FARPROC GetProcAddress( HMODULE mod, const char* proc );
	BOOL IsBadReadPtr( const void* lp, uintptr_t ucb );
	HMODULE LoadLibraryA( const char* file_name );
	int WideCharToMultiByte( UINT CodePage, DWORD dwFlags, LPCWCH lpWideCharStr, int cchWideChar, LPSTR lpMultiByteStr, int cbMultiByte, LPCCH lpDefaultChar, LPBOOL lpUsedDefaultChar );

	// battleye funcs
	void send_report( uint8_t* buffer, size_t size, bool unk );

	static std::unordered_map<std::string, void*> hooked_functions = {
		{ "GetModuleHandleA", ::hooks::GetModuleHandleA },
		{ "GetProcAddress", ::hooks::GetProcAddress },
		{ "IsBadReadPtr", ::hooks::IsBadReadPtr },
		{ "LoadLibraryA", ::hooks::LoadLibraryA },
		{ "WideCharToMultiByte", hooks::WideCharToMultiByte }
	};
}
