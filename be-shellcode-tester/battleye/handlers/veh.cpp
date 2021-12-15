#include "battleye/reports.hpp"


namespace battleye::reports::handlers {
	void veh( battleye::enums::e_report_id id, util::io::reader_t& reader ) {
		util::logger::info( "\thook_id: %d", reader.read<uint8_t>( ) );
		util::logger::info( "\tcalled_by: 0x%p", reader.read<uint64_t>( ) );

		uint8_t dump[ 32 ];
		reader.read_to( dump, 32 );

		util::logger::info( "\tallocation_base: 0x%p", reader.read<uint64_t>( ) );
		util::logger::info( "\tbase_address: 0x%p", reader.read<uint64_t>( ) );
		util::logger::info( "\tregion_size: 0x%x", reader.read<uint32_t>( ) );
		util::logger::info( "\tstate: 0x%x", reader.read<uint32_t>( ) );

		util::logger::info( "\thexdump:" );
		util::hexdump( dump, 32 );
	}
}
