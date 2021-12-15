#include "battleye/reports.hpp"


namespace battleye::reports::handlers {
	void general_info( battleye::enums::e_report_id id, util::io::reader_t& reader ) {
		char buffer[ 256 ] = { '\0' };

		util::logger::info( "\twindows:" );

		auto windows_end = reader.read<uint16_t>( ) + reader.get_buffer( );
		while ( reader.get_buffer( ) < windows_end ) {
			auto window_title_len = reader.read<uint8_t>( );
			if ( window_title_len ) {
				reader.read_to( buffer, window_title_len );
				buffer[ window_title_len ] = '\0';
				util::logger::info( "\t\ttitle: %s", buffer );
			}

			auto window_class_len = reader.read<uint8_t>( );
			if ( window_class_len ) {
				reader.read_to( buffer, window_class_len );
				buffer[ window_class_len ] = '\0';
				util::logger::info( "\t\tclass: %s", buffer );
			}

			auto window_path_len = reader.read<uint8_t>( );
			if ( window_path_len ) {
				reader.read_to( buffer, window_path_len );
				buffer[ window_path_len ] = '\0';
				util::logger::info( "\t\tpath: %s", buffer );
			}

			util::logger::info( "\t\tfile_size: %d", reader.read<uint32_t>( ) );
			util::logger::info( "\t\twindow_style: %x", reader.read<uint32_t>( ) );
			util::logger::info( "\t\twindow_ex_style: %x", reader.read<uint32_t>( ) );

			auto window_rect = reader.read<RECT>( );
			util::logger::info( "\t\twindow_rect.left: %d", window_rect.left );
			util::logger::info( "\t\twindow_rect.top: %d", window_rect.top );
			util::logger::info( "\t\twindow_rect.right: %d", window_rect.right );
			util::logger::info( "\t\twindow_rect.bottom: %d", window_rect.bottom );
			util::logger::info( "\t\t================================" );
		}

		util::logger::info( "\thandles:" );
		auto handles_end = reader.read<uint16_t>( ) + reader.get_buffer( );
		while (reader.get_buffer() < handles_end) {
			auto len = reader.read<uint8_t>( );
			if ( len ) {
				reader.read_to( buffer, len );
				buffer[ len ] = '\0';
				util::logger::info( "\t\tpath: %s", buffer );
			}
			util::logger::info( "\t\tfile_size: %d", reader.read<uint32_t>( ) );
			util::logger::info( "\t\taccess_mask: %x", reader.read<uint32_t>( ) );
			util::logger::info( "\t\t================================" );
		}

		// @fixme: unknown zeroes?
		reader.skip( sizeof( uint32_t ) * 4 );
		
		uint64_t hooked_addr = reader.read<uint64_t>( );
		if ( hooked_addr ) {
			//util::logger::info("\thooked function:\n");
			//util::logger::info("\t\taddress: %p\n", hooked_addr);
			reader.skip( sizeof( uint64_t ) * 3 );
		}

		util::logger::info( "\tsystem:" );
		util::logger::info( "\t\tstartup_time: %d", reader.read<uint32_t>( ) );

		util::logger::info( "\tbootmgfw.efi:" );
		util::logger::info( "\t\tcreated_at: %d", reader.read<uint32_t>( ) );
		util::logger::info( "\t\tlast_access_time: %d", reader.read<uint32_t>( ) );
		util::logger::info( "\t\tlast_write_time: %d", reader.read<uint32_t>( ) );
		util::logger::info( "\t\tchange_time: %d", reader.read<uint32_t>( ) );
		util::logger::info( "\t\tfile_attributes: %d", reader.read<uint32_t>( ) );
	}
}
