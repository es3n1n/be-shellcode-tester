#include "hooks/hooks.hpp"
#include "battleye/battleye.hpp"
#include <vector>


namespace hooks {
	namespace detail {
		static std::vector<std::string> allowed_modules_to_load = {
			"msvcrt.dll", "USER32.dll", "shell32.dll"
		};
	}

	HMODULE GetModuleHandleA( const char* module_name ) {
		util::logger::info( "%s%s%s%s%s", __FUNCTION__, module_name ? "(\"" : "", module_name, module_name ? "\"" : "", module_name ? ")" : "" );

		if ( !module_name ) { // @note: es3n1n: if battleye asks for game handle, then we'll fake it
			static void* fake = nullptr;
			if ( !fake ) {
				fake = malloc( 0xFFFFFF );

				const auto mod = reinterpret_cast< uint8_t* >( ::GetModuleHandleA( NULL ) );
				auto pe = util::c_pe( mod );
				memcpy( fake, mod, pe.get_headers_size( ) );
				// @note: es3n1n: copy only headers and leave everything as it is
			}
			return reinterpret_cast< HMODULE >( fake );
		}

		auto res = battleye::resources_list.find( module_name );
		if ( res != battleye::resources_list.end( ) )
			return reinterpret_cast< HMODULE >( res->second );

		HMODULE ret = ::GetModuleHandleA( module_name );
		if ( !ret ) {
			if ( std::find( detail::allowed_modules_to_load.begin( ), detail::allowed_modules_to_load.end( ), module_name ) != detail::allowed_modules_to_load.end( ) )
				ret = ::LoadLibraryA( module_name );
		}

		//if ( !ret )
		//	util::logger::error( "Module %s not found!", module_name );

		return ret;
	}
}
