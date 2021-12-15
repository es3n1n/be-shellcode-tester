#include "reports.hpp"
#include <cassert>


namespace battleye::reports {
	void register_handlers( ) {
		registered_handlers[ battleye::enums::e_report_id::REPORT_UNKNOWN ] = handlers::unknown;
		registered_handlers[ battleye::enums::e_report_id::REPORT_ENCRYPTED ] = handlers::encrypted;
		registered_handlers[ battleye::enums::e_report_id::REPORT_GENERAL_INFO ] = handlers::general_info;
		registered_handlers[ battleye::enums::e_report_id::REPORT_VEH ] = handlers::veh;
		registered_handlers[ battleye::enums::e_report_id::REPORT_MEMORY_ANOMALY ] = handlers::memory_anomaly;
		registered_handlers[ battleye::enums::e_report_id::REPORT_WINDOW_TITLE ] = handlers::window_title;
		registered_handlers[ battleye::enums::e_report_id::REPORT_MEMORY_SIGNATURE ] = handlers::memory_signature;
		registered_handlers[ battleye::enums::e_report_id::REPORT_DRIVER_PRESENCE_BEEP ] = handlers::driver_presence;
		registered_handlers[ battleye::enums::e_report_id::REPORT_DRIVER_PRESENCE_NULL ] = handlers::driver_presence;
		//registered_handlers[ battleye::enums::e_report_id::REPORT_MEMORY_REGION ] = handlers::memory_region;
		registered_handlers[ battleye::enums::e_report_id::REPORT_BECLIENT_ENCRYPTED ] = handlers::beclient_encrypted;
	}

	void execute_handler( battleye::enums::e_report_id id, util::io::reader_t& reader ) {
		auto handler = registered_handlers.find( id );
		if ( handler == registered_handlers.end( ) )
			return;
		if (id != battleye::enums::e_report_id::REPORT_ENCRYPTED)
			util::logger::info( "[0x%x] Report(%s):", id, enums::report_id_to_string( id ) );
		handler->second( id, reader );
		if ( id != battleye::enums::e_report_id::REPORT_ENCRYPTED )
			util::logger::info( "" );
	}

	void execute_handler( const uint8_t* buffer, size_t size ) {
		auto reader = util::io::reader_t( buffer, size );
		auto id = reader.read<uint8_t>( );
		if ( id == 0x0 ) {
			//util::logger::error( "Got invalid report" );
			return;
		}
		execute_handler( static_cast< enums::e_report_id >( id ), reader );
		//assert( reader.get_size( ) == 0 );
	}
}
