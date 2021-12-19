#include "bootstrap.hpp"
#include "battleye/reports.hpp"
#include "hooks/hooks.hpp"
#include <mutex>


namespace bootstrap {
	namespace detail {
		void init( ) {
			static std::once_flag fl;
			std::call_once( fl, [ ] ( ) -> void {
				util::logger::info( "Registering handlers" );
				battleye::reports::register_handlers( );
			} );
		}
	}

	void run_file( const std::wstring& path, const std::wstring& name ) {
		detail::init( );

		util::logger::info( "Loading %ws", name.c_str( ) );
		loader::load_shellcode( util::io::open_file( path.c_str( ) ) );
	}

	void run_dir( const std::string& dir ) {
		detail::init( );

		util::logger::info( "Iterating dir %s", dir.c_str( ) );

		for ( const auto& entry : std::filesystem::directory_iterator( dir ) ) {
			const auto& path = entry.path( );
			const auto& name = path.filename( );

			// run only .bin files
			if ( name.extension( ) != L".bin" )
				continue;

			run_file( path, name );
		}

		util::logger::info( "Finished" );
	}
}