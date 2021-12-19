#include "battleye/reports.hpp"


namespace battleye::reports::handlers {
	void memory_signature( battleye::enums::e_report_id id, util::io::reader_t& reader ) {
		const auto type = reader.read<uint16_t>( );
		const auto data = reader.read<uint64_t>( );
		const auto base_address = reader.read<uint64_t>( );
		const auto region_size = reader.read<uint32_t>( );
		const auto memory_info = reader.read<uint32_t>( );
		const auto len = strnlen( ( char* )data, 256 );

		util::logger::info( "\ttype: %hx", type );
		util::logger::info( "\tdata: 0x%p", data );
		util::logger::info( "\tbase_address: 0x%p", base_address );
		util::logger::info( "\tregion_size: 0x%x", region_size );
		util::logger::info( "\tmemory_info: %x", memory_info );
		util::logger::info( "\thexdump:" );
		util::hexdump( "\t\t", reinterpret_cast< void* >( data ), ( len != 0 && len != 256 ) ? len : 10 );
	}
}
