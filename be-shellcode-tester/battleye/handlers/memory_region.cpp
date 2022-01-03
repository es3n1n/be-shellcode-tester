#include "battleye/reports.hpp"


namespace battleye::reports::handlers {
	void memory_region( battleye::enums::e_report_id id, util::io::reader_t& reader ) {
		util::logger::info( "\tunk_mem_type: %d", reader.read<uint8_t>( ) );
		util::logger::info( "\tbase_addr: 0x%p", reader.read<uint64_t>( ) );
		util::logger::info( "\tregion_size: 0x%x", reader.read<uint32_t>( ) );
		util::logger::info( "\tregion_flags: %x", reader.read<uint32_t>( ) );

		//size_t sz = reader.get_size( );
		//uint8_t* dump = ( uint8_t* )( malloc( sz ) );
		//reader.read_to( dump, sz );
		//util::logger::info( "\thexdump:" );
		//util::hexdump( "\t\t", dump, sz );
		//free( dump );
		reader.skip( reader.get_size( ) );
	}
}
