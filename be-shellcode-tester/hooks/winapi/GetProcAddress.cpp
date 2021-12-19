#include "hooks/hooks.hpp"


namespace hooks {
	FARPROC GetProcAddress( HMODULE mod, const char* proc ) { 
		util::logger::info( "%s(0x%p, \"%s\")", __FUNCTION__, mod, proc );
		
		auto hk = hooks::hooked_functions.find( proc );
		if ( hk != hooks::hooked_functions.end( ) )
			return static_cast< FARPROC >( hk->second );
		
		return ::GetProcAddress( mod, proc );
	}
}