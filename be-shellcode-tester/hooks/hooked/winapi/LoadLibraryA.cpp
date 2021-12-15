#include "hooks/hooks.hpp"


namespace hooks {
	HMODULE LoadLibraryA( const char* file_name ) {
		util::logger::info( "%s(\"%s\")", __FUNCTION__, file_name );

		HMODULE ret = ::LoadLibraryA( file_name );
		if ( !ret ) {
			util::logger::error( "Failed to load %s", file_name );
		}

		if ( util::str_ends_with( file_name, "BEClient2.dll" ) ) {
			// @note: es3n1n: the trick is that we'll iterate through IAT(Import Address Table) and replace original fn addr with our hk
			auto pe = util::c_pe( reinterpret_cast< uint8_t* >( ret ) );

			for ( auto& [mod, imports] : pe.get_imports( ) ) {
				for ( auto& import_data : imports ) {
					auto hk = hooks::hooked_functions.find( import_data.name );
					if ( hk == hooks::hooked_functions.end( ) ) continue;

					// @note: es3n1n: change protection, and we'll able to write our hooks there
					DWORD old_protection;
					VirtualProtect( reinterpret_cast< void* >( uintptr_t( ret ) + import_data.function_rva ), sizeof( uintptr_t ) * 3, PAGE_EXECUTE_READWRITE, &old_protection );

					// @note: es3n1n: write hook address
					*reinterpret_cast< uintptr_t* >( uintptr_t( ret ) + import_data.function_rva ) = uintptr_t( hk->second );

					// @fixme: es3n1n: GetModuleHandleA import doesn't present in iat idk lol
					if ( !strcmp( import_data.name.c_str( ), "GetProcAddress" ) )
						*reinterpret_cast< uintptr_t* >( uintptr_t( ret ) + import_data.function_rva + sizeof( uintptr_t ) ) = uintptr_t( hooks::hooked_functions[ "GetModuleHandleA" ] );

					// @note: es3n1n: restore protection
					VirtualProtect( reinterpret_cast< void* >( uintptr_t( ret ) + import_data.function_rva ), sizeof( uintptr_t ) * 3, old_protection, &old_protection );
				}
			}
		}

		return ret;
	}
}
