#include "hooks/hooks.hpp"


namespace hooks {
	BOOL IsBadReadPtr( const void* lp, uintptr_t ucb ) { // @note: es3n1n: I've made this hook cz i'm tired of unhandled errors
		MEMORY_BASIC_INFORMATION mbi = { 0 };
		VirtualQuery( lp, &mbi, sizeof( mbi ) );
		if ( !!GetLastError( ) )
			return true;
		bool ret = mbi.Protect & PAGE_EXECUTE_READ;
		ret |= mbi.Protect & PAGE_EXECUTE_READWRITE;
		return !ret;
	}
}
