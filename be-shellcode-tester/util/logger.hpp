#pragma once
#include <cstdint>
#include <stdio.h>
#include <Windows.h>
#include <functional>


#define L_ERROR(...) util::logger::error(__FUNCTION__ "(): " __VA_ARGS__);
#define TRACE_FN util::logger::debug( "%s()", __FUNCTION__ );

#define LOGGER_PARSE_FMT  char buf[1024]; va_list va; va_start( va, fmt ); _vsnprintf_s( buf, 1024, fmt, va ); va_end( va );
#define CREATE_LOGGER_METHOD(n) inline void n(const char* fmt, ...) { LOGGER_PARSE_FMT; log( #n, e_level_color::level_color_ ##n, buf ); }


namespace util {
	namespace logger {
		enum class e_level_color : uint32_t {
			level_color_none = 15, // black bg and white fg
			level_color_debug = 8,
			level_color_info = 10,
			level_color_warn = 14,
			level_color_error = 12
		};

		namespace _colors {
			inline void* m_console_handle = nullptr;

			inline bool ensure_handle( ) {
				if ( !m_console_handle )
					m_console_handle = GetStdHandle( STD_OUTPUT_HANDLE );
				return static_cast< bool >( m_console_handle );
			}

			inline void apply( uint32_t clr ) {
				if ( !ensure_handle( ) ) return;
				SetConsoleTextAttribute( m_console_handle, clr );
			}

			inline void reset( ) {
				apply( static_cast< uint32_t >( e_level_color::level_color_none ) );
			}

			inline void colorify( uint32_t clr, std::function<void( )> cb ) {
				apply( clr );
				cb( );
				reset( );
			}
		}

		inline void log( const char* prefix, e_level_color level, const char* message ) {
			_colors::colorify( static_cast< uint32_t >( level ), [ prefix ] ( ) -> void {
				printf( "%s >> ", prefix );
			} );

			printf( "%s\n", message );
		}

	#ifdef _DEBUG
		CREATE_LOGGER_METHOD( debug );
	#else
		__forceinline void debug( const char* fmt, ... ) { }
	#endif
		CREATE_LOGGER_METHOD( info );
		CREATE_LOGGER_METHOD( warn );
		CREATE_LOGGER_METHOD( error );
		inline void fatal( const char* fmt, ... ) {
			LOGGER_PARSE_FMT;
			error( "Fatal error: %s", buf );
			MessageBoxA( NULL, buf, "Fatal error", MB_OK );
			ExitProcess( -1 );
		}

		inline void pause( ) {
			_colors::colorify( static_cast< uint32_t >( e_level_color::level_color_warn ), [ ] ( ) -> void {
				printf( "warn >> " );
			} );
			printf( "Press any key to continue..." );
			_getwch( );
			printf( "\n" );
		}

		__forceinline void attach( ) {
			::AllocConsole( );
			freopen_s( reinterpret_cast< FILE** >( stdin ), "CONIN$", "r", stdin );
			freopen_s( reinterpret_cast< FILE** >( stdout ), "CONOUT$", "w", stdout );
		}

		__forceinline void detach( ) {
			::ShowWindow( ::GetConsoleWindow( ), SW_HIDE );
			::FreeConsole( );
		}
	}
}

#undef CREATE_LOGGER_METHOD