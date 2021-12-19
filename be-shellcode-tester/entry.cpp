#include "bootstrap/bootstrap.hpp"


#ifndef DLL
int main( int argc, char* argv[ ] ) {
	util::logger::info( "Starting..." );
	bootstrap::run_dir(
		argc >= 2 ? argv[ 1 ] : "C:\\shellcodes\\"
	);
	return EXIT_SUCCESS;
}
#else
DWORD __stdcall th( LPVOID h ) {
	util::logger::attach( );
	util::logger::info( "Starting..." );
	bootstrap::run_dir(
		"C:\\shellcodes\\"
	);
	if ( h )
		FreeLibraryAndExitThread( static_cast< HMODULE >( h ), 0x1 );
	return 1;
}

BOOL __stdcall DllMain( HANDLE h, uint32_t call_reason, uintptr_t reserved ) { 
	if ( call_reason != DLL_PROCESS_ATTACH ) return TRUE;

	CreateThread( 0, 0, th, h, 0, 0 );

	return TRUE;
}
#endif
