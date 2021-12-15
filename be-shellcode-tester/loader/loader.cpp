#include "loader.hpp"


namespace loader {
	bool load_shellcode( util::io::handle_t file_handle ) {
		// @note: es3n1n: assert file
		if ( file_handle == INVALID_HANDLE_VALUE ) {
			util::logger::error( "Got invalid file_handle" );
			util::io::close_file( file_handle );
			return false;
		}

		// @note: es3n1n: read file size, assert it then
		size_t file_size = util::io::get_file_size( file_handle );
		if ( !file_size ) {
			util::logger::error( "Got empty file to load" );
			util::io::close_file( file_handle );
			return false;
		}

		// @note: es3n1n: allocating region for mapped shellcode
		uint8_t* shellcode_region = static_cast< uint8_t* >( VirtualAlloc( NULL, file_size, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE ) );
		if ( !shellcode_region ) {
			util::logger::error( "Failed to allocate memory" );
			util::io::close_file( file_handle );
			return false;
		}

		// @note: es3n1n: reading from file to allocated memory
		if ( !util::io::read_file( file_handle, shellcode_region, file_size ) ) {
			util::logger::error( "Failed to allocate memory" );
			util::io::close_file( file_handle );
			return false;
		}
		util::io::close_file( file_handle );

		// @note: es3n1n: fix some weird check
		uint32_t* report_end = reinterpret_cast< uint32_t* >( reinterpret_cast< uint8_t* >( hooks::send_report ) + 5 );
		if ( *report_end == 0xCCCCCCCC ) {
			DWORD old_protect;
			VirtualProtect( report_end, sizeof( uint32_t ), PAGE_EXECUTE_READWRITE, &old_protect );
			*report_end = 0xCCCC90CC;
			VirtualProtect( report_end, sizeof( uint32_t ), old_protect, &old_protect );
		}

		// @note: es3n1n: ready to run
		util::logger::info( "Ready to run" );
		util::logger::pause( );

		// @note: es3n1n: running
		bool unk = true;
		reinterpret_cast< battleye::typedefs::shellcode_startup_t >( shellcode_region )(
			uintptr_t( shellcode_region ), hooks::send_report, hooks::GetModuleHandleA, hooks::GetProcAddress, &unk
		);

		// @note: es3n1n: cleaning up
		VirtualFree( shellcode_region, 0, MEM_RELEASE );

		return true;
	}
}
