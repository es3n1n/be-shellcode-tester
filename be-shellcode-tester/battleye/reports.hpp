#pragma once
#include "util/util.hpp"
#include "enums.hpp"


namespace battleye::reports {
	using report_handler_t = void( * )( battleye::enums::e_report_id, util::io::reader_t& );

	namespace handlers {
		void encrypted( battleye::enums::e_report_id, util::io::reader_t& reader );
		void general_info( battleye::enums::e_report_id, util::io::reader_t& reader );
		void veh( battleye::enums::e_report_id, util::io::reader_t& reader );
		void memory_anomaly( battleye::enums::e_report_id, util::io::reader_t& reader );
		void window_title( battleye::enums::e_report_id, util::io::reader_t& reader );
		void memory_signature( battleye::enums::e_report_id, util::io::reader_t& reader );
		void driver_presence( battleye::enums::e_report_id, util::io::reader_t& reader );
		//void memory_region( battleye::enums::e_report_id, util::io::reader_t& reader );
		void beclient_encrypted( battleye::enums::e_report_id, util::io::reader_t& reader );
		void mono_assets( battleye::enums::e_report_id, util::io::reader_t& reader );
		
		inline void unknown( battleye::enums::e_report_id, util::io::reader_t& reader ) { 
			util::hexdump( reader.get_buffer( ), reader.get_size( ) );
		}
	}

	static std::unordered_map<battleye::enums::e_report_id, report_handler_t> registered_handlers = { };

	void register_handlers( );
	void execute_handler( battleye::enums::e_report_id id, util::io::reader_t& reader );
	void execute_handler( const uint8_t* buffer, size_t size );
}
